#include <stdlib.h>
#include <stdio.h>
#include "ProductBST.h"

#define ARGC_ERROR_MSG "ERROR: Wrong number of arguments.\nUsage: main <path to file>\n"

/**
 * main to run functions from Ex2
 */
int main (int argc, char *argv[])
{
    /*
    if (argc < 2)
    {
        fprintf (stderr, ARGC_ERROR_MSG);
        return EXIT_FAILURE;  // EXIT_FAILURE is a macro for 1. Only to be used as return value from main or
        // parameter to exit()! Don't use it to replace 1 in function return value etc.
    }

    // parse from file products BST
    Node *root = build_bst (argv[1]);


    // add new product to the tree, search and delete it
    root = add_product (root, "New Laptop", 80);
    Product *new_laptop = search_product (root, "New Laptop");
    root = delete_product (root,"New Laptop");

    // add another new product, and update it
    root = add_product (root, "One More Laptop", 20);
    root = update_quantity (root, "One More Laptop", -1);

    Node *root = build_bst(argv[1]) ;
    */
    Node root;
    Product pro ;
    pro.quantity = 5 ;
    pro.name = "mino" ;
    root.product =pro ;
    //delete_tree (&root);
    printf("%s",root.product.name) ;

    return EXIT_SUCCESS; // macro for 0. Like EXIT_FAILURE, not to be used for function return values!!
}
