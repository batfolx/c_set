#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define HASHSET_SIZE 256

typedef struct hashset_t {
    bool init;
    int64_t ** entries;

} hashset_t;

bool hashset_init(hashset_t *) ;
bool hashset_add(hashset_t *, int64_t key) ;


