#include "tree.h"
#include "set.h"
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


// compare function, compares two elements
int compare (const void * num1, const void * num2) {
    return (*(int64_t *)num1 > *(int64_t *)num2) ? 1 : -1;
}

int main() {
    /*node_t root;
    root.port = 5000;
    root.left = NULL;
    root.right = NULL;
    clock_t time = clock();
    for (int i = 0 ; i < 65535; i++) tree_add(&root, i);
    time = clock() - time;

    printf("This run took %f seconds\n", (double)time / CLOCKS_PER_SEC); */
    SimpleSet set;
    set_init(&set);

    char buff[20];
    printf("Adding to set...\n");
    for (uint64_t i = 0; i < 2550000; i++) {
        snprintf(buff, 20, "%ld", i);
        set_add(&set, buff);
    }
    printf("Finished adding to set\n");

    uint64_t size;
    char ** elements = set_to_array(&set, &size);
    int64_t * numbers = (int64_t *) malloc(size * sizeof(int64_t));

    printf("Adding elements to memory\n");
    for (int i = 0; i < size; i++) {
        int64_t number = (int64_t) strtol(elements[i], NULL, 10);
        numbers[i] = number;
        free(elements[i]);
    }

    printf("Sorting numbers\n");
    qsort(numbers, size, sizeof(int64_t), compare);
    for (int64_t i = 0; i < size; i++) printf("Element in numbers %ld\n", numbers[i]);


    set_destroy(&set);

}
