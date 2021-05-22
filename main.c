#include "hashset.h"

int main() {
    hashset_t set;

    if ( !hashset_init(&set) ) {
        printf("Could not init set\n");
        return -1;
    }



    for (int i = 0; i < 5000000; i++) hashset_add(&set, i);

    uint64_t size = 0;
    int64_t * array = hashset_to_array(&set, &size, true);
    for (int64_t i = 0; i < size; i++) printf("Element in set %ld\n", array[i]);
    printf("Size of set: %ld\n", size);



    printf("Successfully initialized set\n");
}