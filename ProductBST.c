#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProductBST.h"

Node *get_new_node(const Node *root, char *name, int quantity);

int allocate_and_cpy (char *dest , const char *src)
{
    dest = malloc (strlen (src) + 1);
    if (!dest)
    {
        return ALLOCATION_FAILED;
    }
    strcpy (dest, src);
    return EXIT_SUCCESS;
}


Node *bst_root(void)
{
    return calloc (1, sizeof (Node));
}

Node *build_bst (const char *filename)
{
    if(!filename){
        INVALID_POINTER;
    }
    FILE* fp = fopen(filename, "r") ;
    if (!fp){
        return FILE_OPEN_FAILED;
    }
    char buffer[MAX_LINE_LENGTH];
    fgets(buffer, MAX_LINE_LENGTH, fp);
    Product p;
    char *tok = NULL;
    while(fgets(buffer,MAX_LINE_LENGTH+1,fp)){
        tok = strtok(buffer,":");
        if (!tok){
            return INVALID_LINE ;
        }
        if(!(p.quantity = (int)strtol(tok,NULL,10))) {
            return INVALID_LINE ;
        }
        if(!(p.quantity = (int)strtol(tok,NULL,10))) {
            return INVALID_LINE ;
        }



    }

    printf("%s",buffer);
}

Node *add_product (Node *root, char *name, int quantity) {
    if(!root){
        return INVALID_POINTER ;
    }
    if(!name){
        return INVALID_LINE ;
    }
    if(!quantity){
        return INVALID_QUANTITY;
    }
    Node *new_node = get_new_node(root, name, quantity);
    if (!new_node){
        return ALLOCATION_FAILED ;
    }

    return new_node;

}

Node *get_new_node(const Node *root, char *name, int quantity) {
    Product* prud = malloc(sizeof (Product)) ;
    if (!prud) {
        return ALLOCATION_FAILED;
    }
    prud -> quantity = quantity;
    prud ->name = name ;
    Node* node = malloc(sizeof (Node)) ;
    if (!node) {
        return ALLOCATION_FAILED;
    }
    if(!allocate_and_cpy(node->product.name,prud->name)) {
        free(node);
        return EXIT_FAILURE ;
    }
    node->product.quantity = prud->quantity ;
    if(!node->product.quantity){
        free(node);
        free(prud) ;
        return INVALID_QUANTITY ;
    }

    return root;
}

Node *delete_product (Node *root, char *name){
    return root;
}

Product *search_product (Node *root, char *name){
    return root;
}
void delete_tree (Node *root){
}
Node* update_quantity (Node *root, char *name, int amount_to_update){
    return root ;
}