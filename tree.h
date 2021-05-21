#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node_t {
    uint16_t port;
    struct node_t* left;
    struct node_t* right;
} node_t;


int8_t tree_contains(node_t *root, uint16_t key) ;
int8_t tree_add(node_t *root, uint16_t);
