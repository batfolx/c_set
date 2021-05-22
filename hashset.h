#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define HASHSET_SIZE 256
#define HASHSET_ENTRY_DEFAULT_SZ 128

typedef struct hashentry_t {
    int64_t *list;
    int64_t total_sz;
    int64_t index;
} hashentry_t;

typedef struct hashset_t {
    bool init;
    hashentry_t * entries;
} hashset_t;




bool hashset_init(hashset_t *) ;
bool hashset_add(hashset_t *, int64_t key) ;


