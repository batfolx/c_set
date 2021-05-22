#include "hashset.h"

/**
 * Initializes the hashset map
 * @param set The set to be initialized
 * @return true if the set could be initialized, false otherwise
 */
bool hashset_init(hashset_t *set) {

    set->entries = ( hashentry_t * ) malloc(HASHSET_SIZE * sizeof(hashentry_t));
    if ( !set->entries ) {
        set->init = false;
        return false;
    }
    for (int64_t i = 0; i < HASHSET_SIZE; i++) set->entries[i].list = NULL;
    set->init = true;
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

    int64_t mod_key = key % HASHSET_SIZE;
    printf("Key %ld maps to %ld\n", key, mod_key);

    // no entry found here. add to set
    if ( set->entries[mod_key].list == NULL ) {
        set->entries[mod_key].list = ( int64_t * ) malloc(HASHSET_ENTRY_DEFAULT_SZ * sizeof(int64_t));
        set->entries[mod_key].index = 0;
        set->entries[mod_key].total_sz = HASHSET_ENTRY_DEFAULT_SZ;
        set->entries[mod_key].list[set->entries[mod_key].index++] = key;
        printf("Allocated memory successfully with index %ld\n", set->entries[mod_key].index);
        return true;
    }
    // check to make sure set does not contain same item, if it does return true and don't
    // do anything
    for (int64_t i = 0; i < set->entries[mod_key].index; i++) {
        if ( set->entries[mod_key].list[i] == key ) {
            printf("Key %ld already exists in set\n", key);
            return true;
        }
    }

    // store number in memory
    set->entries[mod_key].list[set->entries[mod_key].index++] = key;

    // if too many elements need to be stored, dynamically resize memory
    if ( set->entries[mod_key].index >= set->entries[mod_key].total_sz ) {
        set->entries[mod_key].list = (int64_t *) realloc(set->entries[mod_key].list, (set->entries[mod_key].total_sz * 2) * sizeof(int64_t));
        set->entries[mod_key].total_sz *= 2;
    }

    return true;
}


