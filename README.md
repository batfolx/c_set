<p style="font-size: 34px">
    c_set - a very lightweight set data structure for storing 8 byte integers
</p>

<div>
    <p>
        You can clone the repository and drop the ``hashset.c`` and ``hashset.h`` files in your project and include
        them in order to use them.
    </p>
    <p>
        This set currently works with integers but can be converted to other data types with some work.
    </p>
    <p style="font-size: 30px">
        Code Examples
    </p>
</div>

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
<div>
    <p>
        If you'd like to have a little more control over the set(that is, giving it and its elements size yourself), 
        you can do that as well with the ``hashset_init`` function. Keep in mind that increasing the value ``hashset_elements_initial_sz``
        variable reduces the amount of ``malloc`` calls, but also allocates more initial memory, so keep it low
        if you don't want to hog your system's memory.
    </p>
    <p>
        The variable ``hashset_table_sz`` is the amount of buckets that are held within the
        hash table; that is it holds that many pointers the hashset's entries. So within the
        code example below, 512 pointers to memory locations that will store items of the set.
        I recommend keeping this value to 256, 512, or 1024 as I have found that it performs
        relatively well with those numbers. Of course you may increase it to your needs.
    </p>
    <p>
        The total initial memory allocated when called to ``hashset_init`` will be ``hashset_table_sz`` * ``hashset_elements_initial_sz``
        so keep that in mind as well. So if you had ``hashset_elements_initial_sz`` set to 1, and ``hashset_table_sz`` set to
        512, you will only use 512 bytes initially. Not bad! Of course, the more elements you add, the more memory
        will be allocated.
    </p>
    <p>
        Example below        
    </p>
</div>

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

<div>
    <p style="font-size: 30px">
        Things that have not been implemented yet
    </p>
    <ul>
        <li>
            If the set contains an element. (coming soon!)
        </li>
        <li>
            Remove an element from the set. (also coming soon!)
        </li>    
    </ul>
</div>


