#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProductBST.h"


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

Node get_new_node(Node *root, char *name, int quantity) {
    Product* prud = malloc(sizeof (Product)) ;
    if (!prud) {
        fprintf(stderr, ALLOCATION_FAILED);
        delete_tree(root) ;
        return *root;
    }
    prud -> quantity = quantity;
    prud -> name = name ;
    if(!allocate_and_cpy(root->product.name,prud->name)) {
        fprintf(stderr,INVALID_POINTER) ;
        delete_tree(root) ;
        return *root ;
    }
    root->product = *prud ;
    if(!root->product.quantity){
        fprintf(stderr,INVALID_QUANTITY);
        delete_tree(root) ;
        return *root ;
    }
    return *root;
}

Node *bst_root(void)
{
    return calloc (1, sizeof (Node));
}

Product *bst_root_product(void)
{
    return calloc (1, sizeof (Product));
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
    Node *root = malloc(sizeof (Node)) ;
    Node *root_runner = malloc(sizeof (Node)) ;
    if (!root && !root_runner){
        fclose(fp) ;
        delete_tree(root) ;
        fprintf(stderr,INVALID_POINTER);
        return NULL ;
    }
    root->left_child = root_runner ;

    while(fgets(buffer,MAX_LINE_LENGTH+1,fp)){
        tok = strtok(buffer,":") ;
        if(!tok){
            fclose(fp);
            delete_tree(root) ;
            fprintf(stderr,INVALID_LINE);
            return NULL ;
        }
        strcpy(name, tok) ;
        quant = (int)strtol(strtok(NULL, ":"),NULL ,10) ;
        if(!(quant)) {
            fclose(fp);
            delete_tree(root) ;
            fprintf(stderr,INVALID_LINE);
            return NULL ;
        }

        printf("%s\n" , name) ;
        printf("%d\n" , quant) ;
        add_product(root_runner,name ,quant) ;
    }
    fclose(fp) ;
    return root;
}

Node *add_product (Node *root, char *name, int quantity) {
    printf("in") ;
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
    Product *prodi = bst_root_product() ;
    prodi->name = name ;
    prodi->quantity = quantity ;
    Node *new_node = bst_root() ;
    new_node->product = *prodi ;
    int cmp = strcmp(root->left_child->product.name, new_node->product.name) ;
    if (cmp == 0) {
        delete_tree(new_node) ;
        fprintf(stderr,PRODUCT_EXISTS);
        return root ;
    }
    if (cmp > 0){
        root->left_child = new_node ;
    }
    if (cmp < 0){
        root->right_child = new_node ;
    }
    return root;
}




Node search_node_by_prod(Node *root, char *name){
    if (!root) {
        return *root;
    }
    if(strcmp(root->left_child->product.name , name) == 0) {
        return *root->left_child ;
    }
    if(strcmp(root->right_child->product.name, name)== 0){
        return *root->right_child ;
    }

    int cmp = strcmp(root->product.name, name) ;
    if (cmp == 0) {
        return *root ;
    }
    if (cmp > 0) {
        return search_node_by_prod(root->left_child, name) ;
    }
    return search_node_by_prod(root->right_child, name) ;
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
    char flag;
    if (strcmp(node_to_del.left_child->product.name, name) == 0) {
        flag = 'l' ;
    }
    if (strcmp(node_to_del.right_child->product.name, name) == 0) {
        flag = 'r';
    }
    if(!node_to_del.left_child && !node_to_del.right_child) {
        if (flag == 'l') {
            delete_tree(node_to_del.left_child);
        }
        if (flag == 'r') {
            delete_tree(node_to_del.right_child);
        }
    }
        if(node_to_del.right_child && node_to_del.left_child){
            if(node_to_del.right_child->left_child &&
                            !node_to_del.right_child->right_child){
                Node keeper = *node_to_del.right_child->left_child ;
                delete_tree(node_to_del.right_child) ;
              node_to_del.right_child = &keeper ;
            }
           if(!node_to_del.right_child->left_child &&
                                    node_to_del.right_child->right_child){
                Node keeper = *node_to_del.right_child->right_child ;
               delete_tree(node_to_del.right_child) ;
                node_to_del.right_child = &keeper ;
           }
        }
        if(!node_to_del.right_child && node_to_del.left_child) {
           if (node_to_del.left_child->left_child &&
                            !node_to_del.right_child->right_child) {
                    Node keeper = *node_to_del.left_child->left_child;
                delete_tree(node_to_del.left_child);
                node_to_del.left_child = &keeper;
            }
            if (!node_to_del.left_child->left_child &&
                                node_to_del.left_child->right_child) {
                Node keeper = *node_to_del.left_child->right_child;
                delete_tree(node_to_del.left_child);
                node_to_del.left_child = &keeper;
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
    return &root->product ;
}


void delete_tree (Node *root){
    if (root->left_child == NULL && root->right_child == NULL){
        free(root->product.name) ;
        free(root) ;
        root = NULL ;
        return;
    }
    delete_tree(root->left_child);
    delete_tree(root->right_child);
    free(root->product.name);
    free(root) ;
    root = NULL ;
}

Node* update_quantity (Node *root, char *name, int amount_to_update){
    if (amount_to_update <= 0){
        return root ;
    }
    Product prod = *search_product(root,name);
    prod.quantity += amount_to_update ;
    return root ;
}
