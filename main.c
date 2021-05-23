#include "hashset.h"
#include <time.h>


double test(uint64_t hashset_table_sz, uint64_t hashset_elements_initial_sz, uint64_t num_elements) {
    hashset_t set;
    /* create a set with your own memory requirements */
    if ( !hashset_init(&set, hashset_table_sz, hashset_elements_initial_sz) ) {
        printf("Could not init set\n");
        exit(-1);
    }

    /* add elements to array */
    clock_t t = clock();
    for (int64_t i = 0; i <= num_elements; i++) {
        hashset_add(&set, i);
    }
    t = clock() - t;
    //printf("It took %f seconds to add %ld elements\n", (double)t/CLOCKS_PER_SEC, num_elements);

    /*uint64_t size = 0;
    int64_t * numbers = hashset_to_array(&set, &size, true);
    if ( !numbers ) {
        printf("Failed to convert hashset to array\n");
        exit(-1);
    }

    for (uint64_t i = 0; i < size; i++) {} */

    /* When you are done, free the set. */
    hashset_free(&set);

    return ((double)t)/(double)CLOCKS_PER_SEC;
}


int main() {

    int times = 10;
    uint64_t hashset_table_sz = 1024;
    uint64_t hashset_elements_initial_sz = 1;
    uint64_t num_elements = 10;

    printf("=== STARTING PARAMETERS ===\n");
    printf("HASHSET TABLE SIZE: %ld\nHASHSET ELEMENTS INITIAL SIZE: %ld\n",
           hashset_table_sz, hashset_elements_initial_sz);
    printf("Iterating each test %d times\n", times);
    double amount = 0.0f;
    for (int i = 0; i < times; i++) {
        amount += test(hashset_table_sz, hashset_elements_initial_sz, num_elements);
    }


    printf("It took, on average, %f seconds to add %ld elements\n", amount / times, num_elements);

    for (int k = 0; k < 6; k++) {
        num_elements *= 10;
        amount = 0.0;
        for (int i = 0; i < times; i++) {
            amount += test(hashset_table_sz, hashset_elements_initial_sz, num_elements);
        }
        printf("It took, on average, %f seconds to add %ld elements\n", amount / times, num_elements);
    }

    return 0;
}