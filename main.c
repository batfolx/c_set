#include "hashset.h"

int main() {
    hashset_t set;
    /* create a set with your own memory requirements */
    uint64_t hashset_table_sz = 512;
    uint64_t hashset_elements_initial_sz = 128;
    if ( !hashset_init(&set, hashset_table_sz, hashset_elements_initial_sz) ) {
        printf("Could not init set\n");
        exit(-1);
    }

    /* add elements to array */
    for (int64_t i = 0; i <= 65535; i++) hashset_add(&set, i);

    if ( hashset_contains(&set, 65535) ) printf("Set contains 65535\n");
    else printf("Set does not contain 65535\n");

    if (hashset_contains(&set, 100000) ) printf("Set contains 100000\n");
    else printf("Set does not contain 100000\n");

    /* When you are done, free the set. */
    hashset_free(&set);
    return 0;
}