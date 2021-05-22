##c_set - a very lightweight set data structure for storing 8 byte integers

You can clone the repository and drop the ``hashset.c`` and ``hashset.h`` files in your project and include
them in order to use them.

This set currently works with integers but can be converted to other data types with some work.

##Code example

```
#include "hashset.h"
int main() {
    hashset_t set;
    if ( !hashset_init(&set) ) {
        printf("Could not init set\n");
        exit(-1);
    }

    // add however many entries you want
    int64_t entries = 5000000;
    for (int i = 0; i < entries; i++) hashset_add(&set, i);

    // transform set to array
    // you may pass `true` or `false` to the `hashset_to_array`
    // function to sort the resulting array
    bool sort_set = true;
    uint64_t size = 0;
    int64_t * array = hashset_to_array(&set, &size, sort_set);
    if ( !array ) {
        printf("Could not transform hashset to array.\n");
        exit(-1);
    }
    
    for (int64_t i = 0; i < size; i++) printf("Element in set %ld\n", array[i]);

    // When you are done, free the set.
    hashset_free(&set);
    return 0;

}
```


##Things that have not been implemented

--If the set contains an element. (coming soon!)

--Remove an element from the set. (also coming soon!)