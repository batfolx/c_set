#include "hashset.h"

/**
 * Initializes the hashset map to default parameter
 * (HASHSET_SIZE and HASHSET_ENTRY_DEFAULT_SZ as defined in `hashset.h`)
 * @param set The set to be initialized
 * @return true if the set could be initialized, false otherwise
 */
bool hashset_init_default(hashset_t *set) {

    set->entries = ( hashentry_t * ) malloc(HASHSET_SIZE * sizeof(hashentry_t));
    if ( !set->entries ) {
        set->init = false;
        return false;
    }
    for (int64_t i = 0; i < HASHSET_SIZE; i++) {
        set->entries[i].list = NULL;
        set->entries[i].index = 0;
    }
    set->init = true;
    set->hashset_size = HASHSET_SIZE;
    set->hashset_entry_size = HASHSET_ENTRY_DEFAULT_SZ;
    return true;
}


/**
 * Initializes the hashset map with parameters
 * @param set The set to be initialized
 * @param hashset_size The size of the hash set (number of `buckets`)
 * @param hashset_entry_size The initial size of each entry(bucket) in the hash set
 * @return true if the set could be initialized, false otherwise
 */
bool hashset_init(hashset_t *set, uint64_t hashset_size, uint64_t hashset_entry_size) {

    if ( hashset_size == 0 ) hashset_size = 1;
    if ( hashset_entry_size == 0 ) hashset_entry_size = 1;

    set->entries = ( hashentry_t * ) malloc(hashset_size * sizeof(hashentry_t));
    if ( !set->entries ) {
        set->init = false;
        return false;
    }
    for (int64_t i = 0; i < hashset_size; i++) {
        set->entries[i].list = NULL;
        set->entries[i].index = 0;
    }
    set->init = true;
    set->hashset_size = hashset_size;
    set->hashset_entry_size = hashset_entry_size;
    return true;
}

/**
 * Adds an entry to the hash set
 * @param set The set to be added
 * @param key The key to be added
 * @return true if could add, false if something went wrong
 */
bool hashset_add(hashset_t *set, int64_t key) {
    if ( !set ) return false;
    if ( !set->init ) return false;

    int64_t mod_key = key % set->hashset_size;

    // no entry found here. add to set
    if ( set->entries[mod_key].list == NULL ) {
        set->entries[mod_key].list = ( int64_t * ) malloc(set->hashset_entry_size * sizeof(int64_t));
        set->entries[mod_key].index = 0;
        set->entries[mod_key].total_sz = set->hashset_entry_size;
        set->entries[mod_key].list[set->entries[mod_key].index++] = key;
        return true;
    }
    // check to make sure set does not contain same item, if it does return true and don't
    // do anything
    for (int64_t i = 0; i < set->entries[mod_key].index; i++) {
        if ( set->entries[mod_key].list[i] == key ) {
            return true;
        }
    }

    // store number in memory
    set->entries[mod_key].list[set->entries[mod_key].index++] = key;

    // if too many elements need to be stored, dynamically resize memory
    if ( set->entries[mod_key].index >= set->entries[mod_key].total_sz ) {
        int64_t curr_size = set->entries[mod_key].total_sz;
        //printf("Reallocating memory for key %ld with current size %ld to new size %ld\n", key, curr_size, curr_size * 2);
        set->entries[mod_key].list = (int64_t *) realloc(set->entries[mod_key].list, (curr_size * 2) * sizeof(int64_t));
        set->entries[mod_key].total_sz *= 2;
    }

    return true;
}

/**
 * Retrieves the hashsets size. Checks to make sure
 * the set is initialized properly and if it has proper
 * memory
 * @param set The set to calculate the size
 * @param size A pointer to the size
 * @return true if could calculate size, false otherwise
 */
bool hashset_size(hashset_t * set, uint64_t * size) {
    if ( !set ) return false;
    if ( !size ) return false;
    if ( !set->init ) return false;
    *size = 0;
    for (int64_t i = 0; i < set->hashset_size; i++) {
        *size += set->entries[i].index;
    }
    return true;
}


// compare function, compares two elements
static int compare (const void * num1, const void * num2) {
    return (*(int64_t *)num1 > *(int64_t *)num2) ? 1 : -1;
}

/**
 * Gets a pointer an array of 8 byte integers
 * @param set The set to retrieve the array from
 * @param sz A pointer that will be populated with the size of the
 * returned pointer
 * @param sort whether or not to sort the array
 * @return a int64_t* array (which called must free after done)
 * or NULL if something went wrong
 */
int64_t * hashset_to_array(hashset_t * set, uint64_t * sz, bool sort) {

    if ( !set ) return NULL;
    if ( !set->init ) return NULL;
    if ( !sz ) return NULL;

    uint64_t size = 0;
    if ( !hashset_size(set, &size) ) {
        printf("Something went wrong with hashset_size\n");
        return NULL;
    }
    int64_t *numbers = (int64_t *) malloc(size * sizeof(int64_t));
    if ( !numbers ) {
        printf("hashset_to_array: malloc failed\n");
        return NULL;
    }

    uint64_t counter = 0;
    for (int64_t i = 0; i < set->hashset_size; i++) {
        for (int64_t j = 0; j < set->entries[i].index; j++) {
            numbers[counter++] = set->entries[i].list[j];
        }
    }

    if ( sort ) qsort(numbers, size, sizeof(int64_t), compare);
    *sz = size;
    return numbers;
}

/**
 * Frees the sets memory.
 * @param set The set's memory to be freed
 */
void hashset_free(hashset_t * set) {
    if ( !set ) return;
    if ( !set->init ) return;

    // iterate over how many 'buckets' the set has
    // and free valid memory
    for (int64_t i = 0; i < set->hashset_size; i++)
        if ( set->entries[i].list != NULL ) {
            free(set->entries[i].list);
            set->entries[i].index = 0;
            set->entries[i].total_sz = 0;
        }

    set->init = false;
}