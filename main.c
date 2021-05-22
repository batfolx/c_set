#include "hashset.h"

int main() {
    hashset_t set;

    if ( !hashset_init_default(&set) ) {
        printf("Could not init set\n");
        exit(-1);
    }

    /* add elements to array */
    for (int64_t i = 0; i <= 65535; i++) hashset_add(&set, i);

    /* transform set to array, passing true to sort or false to not sort */
    bool sort_set = true;
    uint64_t size = 0;
    int64_t * array = hashset_to_array(&set, &size, sort_set);
    if ( !array ) {
        printf("Could not transform hashset to array.\n");
        exit(-1);
    }

    /* do stuff with each number */
    for (int64_t i = 0; i < size; i++) printf("Element in set %ld\n", array[i]);

    /* When you are done, free the set. */
    hashset_free(&set);
    return 0;

}