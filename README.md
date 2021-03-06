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
            Remove an element from the set. (also coming soon!)
        </li>    
    </ul>
</div>

<p style="font-size: 32px">
    Diagnostics and performance
</p>
<p>
    Below I have ran some small tests to see time performance with
    different parameters. I did this on a system that has the following
    hardware
</p>
<ul>
    <li>
        32GB DDR4 3200MHz RAM
    </li>
    <li>
        Intel core i9-9900K
    </li>
    <li>
        512GB SSD
    </li>
</ul>


<p>
    Below is a big text dump of the tests I ran. Interestingly enough,
    keeping the hashset bucket initial size smaller resulted in a better
    performance (with a larger input) than if it had started with a large initial
    size. I suppose it is because it is more space efficient, as a larger
    initial size may not be used up ever but it is quite expensive to allocate
    a large block of memory as opposed to a small block.
</p>

As you can see, increasing hash table size increases the time performance by quite a bit.
```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 32
HASHSET ELEMENTS INITIAL SIZE: 32
Iterating each test 10 times
It took, on average, 0.000000 seconds to add 10 elements
It took, on average, 0.000003 seconds to add 100 elements
It took, on average, 0.000042 seconds to add 1000 elements
It took, on average, 0.002664 seconds to add 10000 elements
It took, on average, 0.246791 seconds to add 100000 elements
It took, on average, 26.388674 seconds to add 1000000 elements
It took, on average, 2560.489962 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 512
HASHSET ELEMENTS INITIAL SIZE: 256
Iterating each test 10 times
It took, on average, 0.000003 seconds to add 10 elements
It took, on average, 0.000016 seconds to add 100 elements
It took, on average, 0.000152 seconds to add 1000 elements
It took, on average, 0.000432 seconds to add 10000 elements
It took, on average, 0.017279 seconds to add 100000 elements
It took, on average, 1.469125 seconds to add 1000000 elements
It took, on average, 175.148662 seconds to add 10000000 elements
```


```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 1
Iterating each test 10 times
It took, on average, 0.000001 seconds to add 10 elements
It took, on average, 0.000006 seconds to add 100 elements
It took, on average, 0.000026 seconds to add 1000 elements
It took, on average, 0.000298 seconds to add 10000 elements
It took, on average, 0.009568 seconds to add 100000 elements
It took, on average, 0.787694 seconds to add 1000000 elements
It took, on average, 107.157357 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 1
Iterating each test 10 times
It took, on average, 0.000000 seconds to add 10 elements
It took, on average, 0.000003 seconds to add 100 elements
It took, on average, 0.000027 seconds to add 1000 elements
It took, on average, 0.000317 seconds to add 10000 elements
It took, on average, 0.009770 seconds to add 100000 elements
It took, on average, 0.949572 seconds to add 1000000 elements
It took, on average, 108.068025 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 16
Iterating each test 10 times
It took, on average, 0.000000 seconds to add 10 elements
It took, on average, 0.000005 seconds to add 100 elements
It took, on average, 0.000031 seconds to add 1000 elements
It took, on average, 0.000213 seconds to add 10000 elements
It took, on average, 0.009723 seconds to add 100000 elements
It took, on average, 0.977923 seconds to add 1000000 elements
It took, on average, 107.765407 seconds to add 10000000 elements
```

These two vary greatly, might need to run another series of tests
```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 64
Iterating each test 10 times
It took, on average, 0.000001 seconds to add 10 elements
It took, on average, 0.000010 seconds to add 100 elements
It took, on average, 0.000116 seconds to add 1000 elements
It took, on average, 0.000449 seconds to add 10000 elements
It took, on average, 0.016369 seconds to add 100000 elements
It took, on average, 1.650607 seconds to add 1000000 elements
It took, on average, 112.726419 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 64
Iterating each test 10 times
It took, on average, 0.000001 seconds to add 10 elements
It took, on average, 0.000007 seconds to add 100 elements
It took, on average, 0.000083 seconds to add 1000 elements
It took, on average, 0.000299 seconds to add 10000 elements
It took, on average, 0.009605 seconds to add 100000 elements
It took, on average, 0.855675 seconds to add 1000000 elements
It took, on average, 82.628188 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 256
Iterating each test 10 times
It took, on average, 0.000004 seconds to add 10 elements
It took, on average, 0.000019 seconds to add 100 elements
It took, on average, 0.000323 seconds to add 1000 elements
It took, on average, 0.000541 seconds to add 10000 elements
It took, on average, 0.010183 seconds to add 100000 elements
It took, on average, 0.771720 seconds to add 1000000 elements
It took, on average, 94.457552 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 512
Iterating each test 10 times
It took, on average, 0.000005 seconds to add 10 elements
It took, on average, 0.000047 seconds to add 100 elements
It took, on average, 0.000688 seconds to add 1000 elements
It took, on average, 0.000935 seconds to add 10000 elements
It took, on average, 0.010699 seconds to add 100000 elements
It took, on average, 0.807601 seconds to add 1000000 elements
It took, on average, 94.653862 seconds to add 10000000 elements
```


```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 1024
HASHSET ELEMENTS INITIAL SIZE: 1024
Iterating each test 10 times
It took, on average, 0.000003 seconds to add 10 elements
It took, on average, 0.000057 seconds to add 100 elements
It took, on average, 0.000640 seconds to add 1000 elements
It took, on average, 0.000867 seconds to add 10000 elements
It took, on average, 0.010960 seconds to add 100000 elements
It took, on average, 0.840234 seconds to add 1000000 elements
It took, on average, 94.717185 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 2048
HASHSET ELEMENTS INITIAL SIZE: 1
Iterating each test 10 times
It took, on average, 0.000001 seconds to add 10 elements
It took, on average, 0.000005 seconds to add 100 elements
It took, on average, 0.000041 seconds to add 1000 elements
It took, on average, 0.000331 seconds to add 10000 elements
It took, on average, 0.005798 seconds to add 100000 elements
It took, on average, 0.465864 seconds to add 1000000 elements
It took, on average, 46.575807 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 2048
HASHSET ELEMENTS INITIAL SIZE: 2
Iterating each test 10 times
It took, on average, 0.000000 seconds to add 10 elements
It took, on average, 0.000003 seconds to add 100 elements
It took, on average, 0.000028 seconds to add 1000 elements
It took, on average, 0.000304 seconds to add 10000 elements
It took, on average, 0.005668 seconds to add 100000 elements
It took, on average, 0.414972 seconds to add 1000000 elements
It took, on average, 63.144309 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 2048
HASHSET ELEMENTS INITIAL SIZE: 16
Iterating each test 10 times
It took, on average, 0.000000 seconds to add 10 elements
It took, on average, 0.000005 seconds to add 100 elements
It took, on average, 0.000034 seconds to add 1000 elements
It took, on average, 0.000201 seconds to add 10000 elements
It took, on average, 0.005536 seconds to add 100000 elements
It took, on average, 0.424195 seconds to add 1000000 elements
It took, on average, 63.453572 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 2048
HASHSET ELEMENTS INITIAL SIZE: 32
Iterating each test 10 times
It took, on average, 0.000001 seconds to add 10 elements
It took, on average, 0.000009 seconds to add 100 elements
It took, on average, 0.000055 seconds to add 1000 elements
It took, on average, 0.000252 seconds to add 10000 elements
It took, on average, 0.005547 seconds to add 100000 elements
It took, on average, 0.439594 seconds to add 1000000 elements
It took, on average, 72.905465 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 2048
HASHSET ELEMENTS INITIAL SIZE: 256
Iterating each test 10 times
It took, on average, 0.000004 seconds to add 10 elements
It took, on average, 0.000022 seconds to add 100 elements
It took, on average, 0.000305 seconds to add 1000 elements
It took, on average, 0.000843 seconds to add 10000 elements
It took, on average, 0.006653 seconds to add 100000 elements
It took, on average, 0.459155 seconds to add 1000000 elements
It took, on average, 65.102032 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 2048
HASHSET ELEMENTS INITIAL SIZE: 2048
Iterating each test 10 times
It took, on average, 0.000006 seconds to add 10 elements
It took, on average, 0.000063 seconds to add 100 elements
It took, on average, 0.000652 seconds to add 1000 elements
It took, on average, 0.001618 seconds to add 10000 elements
It took, on average, 0.007994 seconds to add 100000 elements
It took, on average, 0.489360 seconds to add 1000000 elements
It took, on average, 48.990473 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 65535
HASHSET ELEMENTS INITIAL SIZE: 2048
Iterating each test 10 times
It took, on average, 0.000005 seconds to add 10 elements
It took, on average, 0.000079 seconds to add 100 elements
It took, on average, 0.000733 seconds to add 1000 elements
It took, on average, 0.007960 seconds to add 10000 elements
It took, on average, 0.055972 seconds to add 100000 elements
It took, on average, 0.166300 seconds to add 1000000 elements
It took, on average, 3.193279 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 131072
HASHSET ELEMENTS INITIAL SIZE: 2048
Iterating each test 10 times
It took, on average, 0.000005 seconds to add 10 elements
It took, on average, 0.000076 seconds to add 100 elements
It took, on average, 0.000788 seconds to add 1000 elements
It took, on average, 0.008025 seconds to add 10000 elements
It took, on average, 0.081300 seconds to add 100000 elements
It took, on average, 0.197650 seconds to add 1000000 elements
It took, on average, 2.251245 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 262144
HASHSET ELEMENTS INITIAL SIZE: 1
Iterating each test 10 times
It took, on average, 0.000002 seconds to add 10 elements
It took, on average, 0.000003 seconds to add 100 elements
It took, on average, 0.000025 seconds to add 1000 elements
It took, on average, 0.000234 seconds to add 10000 elements
It took, on average, 0.002342 seconds to add 100000 elements
It took, on average, 0.037554 seconds to add 1000000 elements
It took, on average, 0.680473 seconds to add 10000000 elements
```


```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 8388608
HASHSET ELEMENTS INITIAL SIZE: 1
Iterating each test 10 times
It took, on average, 0.000003 seconds to add 10 elements
It took, on average, 0.000005 seconds to add 100 elements
It took, on average, 0.000028 seconds to add 1000 elements
It took, on average, 0.000250 seconds to add 10000 elements
It took, on average, 0.002425 seconds to add 100000 elements
It took, on average, 0.023860 seconds to add 1000000 elements
It took, on average, 0.271357 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 8388608
HASHSET ELEMENTS INITIAL SIZE: 16
Iterating each test 10 times
It took, on average, 0.000003 seconds to add 10 elements
It took, on average, 0.000008 seconds to add 100 elements
It took, on average, 0.000063 seconds to add 1000 elements
It took, on average, 0.000500 seconds to add 10000 elements
It took, on average, 0.004881 seconds to add 100000 elements
It took, on average, 0.048106 seconds to add 1000000 elements
It took, on average, 0.460943 seconds to add 10000000 elements
```

```
=== STARTING PARAMETERS ===
HASHSET TABLE SIZE: 8388608
HASHSET ELEMENTS INITIAL SIZE: 32
Iterating each test 10 times
It took, on average, 0.000003 seconds to add 10 elements
It took, on average, 0.000009 seconds to add 100 elements
It took, on average, 0.000075 seconds to add 1000 elements
It took, on average, 0.000735 seconds to add 10000 elements
It took, on average, 0.007264 seconds to add 100000 elements
It took, on average, 0.072452 seconds to add 1000000 elements
It took, on average, 0.676848 seconds to add 10000000 elements
```
