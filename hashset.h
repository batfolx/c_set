#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define HASHSET_SIZE 2048
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
bool hashset_size(hashset_t *, uint64_t *) ;
void hashset_free(hashset_t *);
int64_t * hashset_to_array(hashset_t *, uint64_t*, bool) ;



static int compare (const void * num1, const void * num2);


