##c_set - a very lightweight set data structure for storing 8 byte integers

You can clone the repository and drop the ``hashset.c`` and ``hashset.h`` files in your project and include
them in order to use them.

This set currently works with integers but can be converted to other data types with some work.

##Code example

```
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
```

If you'd like to have a little more control over the set(that is, giving it and its elements size yourself), 
you can do that as well with the ``hashset_init`` function.

Example below
```
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
```


##Things that have not been implemented

--If the set contains an element. (coming soon!)

--Remove an element from the set. (also coming soon!)