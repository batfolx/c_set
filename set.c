
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"

#define MAX_FULLNESS_PERCENT 0.25       /* arbitrary */

/* PRIVATE FUNCTIONS */
static uint64_t __default_hash(const char *key);
static int __get_index(SimpleSet *set, const char *key, uint64_t hash, uint64_t *index);
static int __assign_node(SimpleSet *set, const char *key, uint64_t hash, uint64_t index);
static void __free_index(SimpleSet *set, uint64_t index);
static int __set_contains(SimpleSet *set, const char *key, uint64_t hash);
static int __set_add(SimpleSet *set, const char *key, uint64_t hash);
static void __relayout_nodes(SimpleSet *set, uint64_t start, short end_on_null);

/*******************************************************************************
***        FUNCTIONS DEFINITIONS
*******************************************************************************/

int set_init_alt(SimpleSet *set, uint64_t num_els, set_hash_function hash) {
    set->nodes = (simple_set_node**) malloc(num_els * sizeof(simple_set_node*));
    if (set->nodes == NULL) {
        return SET_MALLOC_ERROR;
    }
    set->number_nodes = num_els;
    uint64_t i;
    for (i = 0; i < set->number_nodes; ++i) {
        set->nodes[i] = NULL;
    }
    set->used_nodes = 0;
    set->hash_function = (hash == NULL) ? &__default_hash : hash;
    return SET_TRUE;
}

int set_clear(SimpleSet *set) {
    uint64_t i;
    for(i = 0; i < set->number_nodes; ++i) {
        if (set->nodes[i] != NULL) {
            __free_index(set, i);
        }
    }
    set->used_nodes = 0;
    return SET_TRUE;
}

int set_destroy(SimpleSet *set) {
    set_clear(set);
    free(set->nodes);
    set->number_nodes = 0;
    set->used_nodes = 0;
    set->hash_function = NULL;
    return SET_TRUE;
}

int set_add(SimpleSet *set, const char *key) {
    uint64_t hash = set->hash_function(key);
    return __set_add(set, key, hash);
}

int set_contains(SimpleSet *set, const char *key) {
    uint64_t index, hash = set->hash_function(key);
    return __get_index(set, key, hash, &index);
}

int set_remove(SimpleSet *set, const char *key) {
    uint64_t index, hash = set->hash_function(key);
    int pos = __get_index(set, key, hash, &index);
    if (pos != SET_TRUE) {
        return pos;
    }
    // remove this node
    __free_index(set, index);
    // re-layout nodes
    __relayout_nodes(set, index, 0);
    --set->used_nodes;
    return SET_TRUE;
}

uint64_t set_length(SimpleSet *set) {
    return set->used_nodes;
}

char** set_to_array(SimpleSet *set, uint64_t *size) {
    *size = set->used_nodes;
    char** results = (char**)calloc(set->used_nodes + 1, sizeof(char*));
    uint64_t i, j = 0;
    size_t len;
    for (i = 0; i < set->number_nodes; ++i) {
        if (set->nodes[i] != NULL) {
            len = strlen(set->nodes[i]->_key);
            results[j] = (char*)calloc(len + 1, sizeof(char));
            memcpy(results[j], set->nodes[i]->_key, len);
            ++j;
        }
    }
    return results;
}



/*******************************************************************************
***        PRIVATE FUNCTIONS
*******************************************************************************/
static uint64_t __default_hash(const char *key) {
    // FNV-1a hash (http://www.isthe.com/chongo/tech/comp/fnv/)
    size_t i, len = strlen(key);
    uint64_t h = 14695981039346656073ULL; // FNV_OFFSET 64 bit
    for (i = 0; i < len; ++i) {
        h = h ^ (unsigned char) key[i];
        h = h * 1099511628211ULL; // FNV_PRIME 64 bit
    }
    return h;
}

static int __set_contains(SimpleSet *set, const char *key, uint64_t hash) {
    uint64_t index;
    return __get_index(set, key, hash, &index);
}

static int __set_add(SimpleSet *set, const char *key, uint64_t hash) {
    uint64_t index;
    if (__set_contains(set, key, hash) == SET_TRUE)
        return SET_ALREADY_PRESENT;

    // Expand nodes if we are close to our desired fullness
    if ((float)set->used_nodes / set->number_nodes > MAX_FULLNESS_PERCENT) {
        uint64_t num_els = set->number_nodes * 2; // we want to double each time
        simple_set_node** tmp = (simple_set_node**)realloc(set->nodes, num_els * sizeof(simple_set_node*));
        if (tmp == NULL || set->nodes == NULL) // malloc failure
            return SET_MALLOC_ERROR;

        set->nodes = tmp;
        uint64_t i, orig_num_els = set->number_nodes;
        for (i = orig_num_els; i < num_els; ++i)
            set->nodes[i] = NULL;

        set->number_nodes = num_els;
        // re-layout all nodes
        __relayout_nodes(set, 0, 1);
    }
    // add element in
    int res = __get_index(set, key, hash, &index);
    if (res == SET_FALSE) { // this is the first open slot
        __assign_node(set, key, hash, index);
        ++set->used_nodes;
        return SET_TRUE;
    }
    return res;
}

static int __get_index(SimpleSet *set, const char *key, uint64_t hash, uint64_t *index) {
    uint64_t i, idx;
    idx = hash % set->number_nodes;
    i = idx;
    size_t len = strlen(key);
    while (1) {
        if (set->nodes[i] == NULL) {
            *index = i;
            return SET_FALSE; // not here OR first open slot
        } else if (hash == set->nodes[i]->_hash && len == strlen(set->nodes[i]->_key) && strncmp(key, set->nodes[i]->_key, len) == 0) {
            *index = i;
            return SET_TRUE;
        }
        ++i;
        if (i == set->number_nodes)
            i = 0;
        if (i == idx) // this means we went all the way around and the set is full
            return SET_CIRCULAR_ERROR;
    }
}

static int __assign_node(SimpleSet *set, const char *key, uint64_t hash, uint64_t index) {
    size_t len = strlen(key);
    set->nodes[index] = (simple_set_node*)malloc(sizeof(simple_set_node));
    set->nodes[index]->_key = (char*)calloc(len + 1, sizeof(char));
    memcpy(set->nodes[index]->_key, key, len);
    set->nodes[index]->_hash = hash;
    return SET_TRUE;
}

static void __free_index(SimpleSet *set, uint64_t index) {
    free(set->nodes[index]->_key);
    free(set->nodes[index]);
    set->nodes[index] = NULL;
}

static void __relayout_nodes(SimpleSet *set, uint64_t start, short end_on_null) {
    uint64_t index = 0, i;
    for (i = start; i < set->number_nodes; ++i) {
        if(set->nodes[i] != NULL) {
            __get_index(set, set->nodes[i]->_key, set->nodes[i]->_hash, &index);
            if (i != index) { // we are moving this node
                __assign_node(set, set->nodes[i]->_key, set->nodes[i]->_hash, index);
                __free_index(set, i);
            }
        } else if (end_on_null == 0 && i != start) {
            break;
        }
    }
}