#include "tree.h"
#include "set.h"
#include "hashset.h"
#include <stdlib.h>

int8_t tree_contains(node_t *root, uint16_t key) {

    if ( key == root->port ) return 1;
    if ( root->left != NULL ) tree_contains(root->left, key);
    if ( root->right != NULL ) tree_contains(root->right, key);
    return -1;
}
int8_t tree_add(node_t *root, uint16_t key) {
    if ( key < root->port ) {
        if ( !root->left ) {
            root->left = (node_t *) malloc(sizeof(node_t));
            root->left->port = key;
            root->left->left = NULL;
            root->left->right = NULL;
            return 1;
        } else {
            return tree_add(root->left, key);
        }

    } else if ( key > root->port ) {
        if ( !root->right ) {
            root->right = (node_t *) malloc(sizeof(node_t));
            root->right->port = key;
            root->right->left = NULL;
            root->right->right = NULL;
            return 1;
        } else {
            return tree_add(root->right, key);
        }

    } else if ( key == root->port ) {
        // do nothing
    }

    return 1;
}

void print_root(node_t* root) {
    if ( root->left != NULL )  print_root(root->left);
    if ( root->right != NULL ) print_root(root->right);
    printf("Root with port %d\n", root->port);
}

