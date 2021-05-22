#include "hashset.h"

/**
 * Initializes the hashset map
 * @param set The set to be initialized
 * @return true if the set could be initialized, false otherwise
 */
bool hashset_init(hashset_t *set) {

    set->entries = ( int64_t ** ) malloc(HASHSET_SIZE * sizeof(int64_t *));
    if ( !set->entries ) {
        set->init = false;
        return false;
    }
    for (int64_t i = 0; i < HASHSET_SIZE; i++) set->entries[i] = NULL;

    set->init = true;
    return true;
}
bool hashset_add(hashset_t *set, int64_t key) {
    if ( !set ) return false;
    if ( !set->init ) return false;

    return true;
}
