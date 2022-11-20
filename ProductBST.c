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
        fprintf(stderr,ALLOCATION_FAILED) ;
        return EXIT_FAILURE;
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
        fprintf(stderr,INVALID_POINTER);
        return NULL ;
    }
    FILE* fp = fopen(filename, "r") ;
    if (!fp){
        fprintf(stderr,FILE_OPEN_FAILED);
        return NULL ;
    }
    char buffer[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];
    int quant;
    char *tok = NULL;
    Node *root = bst_root() ;
    if (!root){
        fclose(fp) ;
        delete_tree(root) ;
        fprintf(stderr,INVALID_POINTER);
        return NULL ;
    }
    while(fgets(buffer,MAX_LINE_LENGTH+1,fp)){
        if(!(tok = strtok(buffer,":"))){
            fclose(fp);
            delete_tree(root) ;
            fprintf(stderr,INVALID_LINE);
            return NULL ;
        }
        strcpy(tok, name) ;
        if(!(quant = (int)strtol(strtok(NULL, ":"),NULL ,10))) {
            fclose(fp);
            delete_tree(root) ;
            fprintf(stderr,INVALID_LINE);
            return NULL ;
        }
        add_product(root,name,quant) ;
    }
    fclose(fp) ;
    return root;
}

Node *add_product (Node *root, char *name, int quantity) {
    if(!root){
        fprintf(stderr,INVALID_POINTER);
        return NULL ;
    }
    if(!name){
        fprintf(stderr,INVALID_LINE);
        return NULL ;
    }
    if(!quantity){
        fprintf(stderr,INVALID_QUANTITY);
        return NULL ;
    }
    int cmp = strcmp(root->product.name, name) ;
    if (cmp == 0) {
        fprintf(stderr,p);
        return NULL ;
        return PRODUCT_EXISTS ;
    }
    Node *new_node = get_new_node(root, name, quantity);
    if (cmp > 1){
        root->left_child = new_node ;
    }
    if (cmp < 1){
        root->right_child = new_node ;
    }
    return new_node;

}

Node *get_new_node(const Node *root, char *name, int quantity) {
    Product* prud = malloc(sizeof (Product)) ;
    if (!prud) {
        return ALLOCATION_FAILED;
    }
    prud -> quantity = quantity;
    prud -> name = name ;
    if(!allocate_and_cpy(root->product.name,prud->name)) {
        delete_tree(root) ;
        return EXIT_FAILURE ;
    }
    root->product.quantity = prud->quantity ;
    if(!root->product.quantity){
        delete_tree(root) ;
        return INVALID_QUANTITY ;
    }
    return root;
}


Node search_node_by_prod(Node *root, char *name){
    if (!root) {
        return *root ;
    }
    int cmp = strcmp(root->product.name, name) ;
    if (cmp == 0) {
        return *root ;
    }
    if (cmp > 0) {
        return search_node_by_prod(root->left_child, name) ;
    }
    return search_node_by_prod(root->right_child, name)
}

Node *find_suc (Node* root){
    if(root->left_child == NULL) {
        return root ;
    }
    return find_suc(root->left_child) ;
}

Node *delete_product (Node *root, char *name){
    if (!(root)){
        fprintf(stderr,INVALID_POINTER) ;
        return root;
    }
    Node node_to_del = search_node_by_prod(root, name) ;
    if(!node_to_del.left_child && !node_to_del.right_child){
        delete_tree(&node_to_del) ;
    }
    if(node_to_del.right_child && node_to_del.left_child){
        if(node_to_del.right_child->left_child && !node_to_del.right_child->right_child){
            Node keeper = *node_to_del.right_child->left_child ;
            delete_tree(node_to_del.right_child) ;
            node_to_del.right_child = &keeper ;
        }
        if(!node_to_del.right_child->left_child && node_to_del.right_child->right_child){
            Node keeper = *node_to_del.right_child->right_child ;
            delete_tree(node_to_del.right_child) ;
            node_to_del.right_child = &keeper ;
        }
    }
    if(!node_to_del.right_child && node_to_del.left_child) {
        if (node_to_del.left_child->left_child && !node_to_del.right_child->right_child) {
            Node keeper = *node_to_del.left_child->left_child;
            delete_tree(node_to_del.left_child);
            node_to_del.left_child = &keeper;
        }
        if (!root->left_child->left_child && root->left_child->right_child) {
            Node keeper = root->left_child->right_child;
            delete_tree(root->left_child);
            root->left_child = &keeper;
        }
    }





    return root ;
}



Product *search_product (Node *root, char *name){
    Product prud =root->product ;
    int cmp = strcmp(prud.name, name) ;
    if (cmp == 0 ) {
        return &root->product ;
    }
    if (cmp > 0) {
        if (root->right_child) {
            return search_product(root->right_child, name);
        }
    }
    if (cmp < 0) {
        if(root->left_child) {
            return search_product(root->left_child, name);
        }

    }
}


void delete_tree (Node *root){
    if (!root){
        return;
    }
    delete_tree(root->right_child) ;
    delete_tree(root->left_child) ;
    free(root->right_child);
    free(root->left_child);
}
Node* update_quantity (Node *root, char *name, int amount_to_update){
    return root ;
}
