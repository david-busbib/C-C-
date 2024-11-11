#ifdef OH_TESTS
#include "oh_tests/oh_tests_helpers.h"
#define malloc test_malloc
#define calloc test_calloc
#define free test_free
#define stderr get_test_stderr()
#endif // OH_TESTS

#include "ProductBST.h"
#define MAX 1025
#include <string.h>
#define R 20
#define L l
#define NOT_INT 1
#define ROOT_DEL 1
#include <ctype.h>
#define BAD_INPUT 1

char * allocate_and_cpy (const char *p)
{
    //this func copy the name and put place in the zicaron
    int l= strlen(p);
    char *new = malloc (l + 1);
    if (!new)
    {
        fprintf(stderr,ERROR ALLOCATION_FAILED);
        free(new);
        return NULL;
    }
    strcpy (new, p);
    return new;
}
Node *create_root(Node *root, char *name, int quantity){
    //in this func we are creating new root
    root = calloc(1, sizeof(Node));
    char *cop=allocate_and_cpy(name);
    if (!cop){
        return NULL;
    }
    if(!root)
    {
        return NULL;
    }
    Product p={cop,quantity};
    root->product=p;
    return root;
}
Node *help_to_search (Node *cur, char *name){
    //this func help to search and return a pointer
    // to the product you want to find
    while(cur) {
        if (strcmp(cur->product.name, name) == 0) {
            return cur;
        }
        else if (strcmp(cur->product.name, name) > 0) {
            cur = cur->left_child;
        }
        else if (strcmp(cur->product.name, name) < 0) {
            cur = cur->right_child;
        }
    }
    return NULL;

}
Product *search_product (Node *root, char *name)
{//this finc shearch product
    if (!root ){
        fprintf(stderr,ERROR INVALID_POINTER);
        return NULL;
    }
    if (!name){
        fprintf(stderr,ERROR PRODUCT_NOT_FOUND);
        return NULL;
    }
    return &help_to_search(root,name)->product;
}
Node *help_to_add (Node *root,Node *cur, char *name, int quantity){
    //this func help to add a new name to the tree
    // and also its value
    //the sum
    Node *prev =NULL;
    int ind=0;
    while(cur) {
        prev = cur;
        if (strcmp(name,cur->product.name) == 0) {
            fprintf(stderr, ERROR PRODUCT_EXISTS);
            return root;
        }
        else if (strcmp(cur->product.name, name) < 0) {
            ind=1;
            cur = cur->right_child;
        }
        else if (strcmp(cur->product.name, name) > 0) {
            ind=0;
            cur = cur->left_child;
        }
    }
    if (ind==1){
        prev->right_child=create_root(prev->right_child,\
        name,quantity);
        return root;
    }
    else{
        prev->left_child=create_root(prev->left_child,\
        name,quantity);
        return root;
    }
}
Node *add_product (Node *root, char *name, int quantity){
    //this func we ading value un case of
    // failer the func return the root and print a msg

    if (quantity<=0){
        fprintf(stderr,ERROR INVALID_QUANTITY);
        return root;
    }
    if (!name){
        fprintf(stderr,ERROR);
        return root;
    }
    if (!root){
        return create_root(root,name,quantity);
    }
    else{
        return help_to_add(root,root,name,quantity);
    }
}
Node *help_to_update (Node *root,Node *cur,\
char *name, int quantity,int sign){
    /*
     * this func help to apdate the sum in case of failuir the func return null
     * if the new value is negative we are caling the delete to delete
     * //sign is 1 if the new amont is negatife else 0
     */
    while(cur) {
        if (strcmp(cur->product.name, name) == 0) {
            if (sign == 0) {
                cur->product.quantity += quantity;
                return NULL;
            }
                // i know that the value is negatife
            else {
                int value = cur->product.quantity  - abs(quantity);
                if (value == 0) {
                    delete_product(root,name);
                    return NULL;
                }
                if (value < 0) {
                    fprintf(stderr, ERROR INVALID_QUANTITY);
                    return NULL;
                } else {
                    cur->product.quantity = value;
                    return NULL;
                }
            }

        } else if (strcmp(cur->product.name, name) > 0) {
            cur = cur->left_child;
        } else if (strcmp(cur->product.name, name) < 0) {
            cur = cur->right_child;
        }
    }
    //if the func arrive here that mean that the name is not found
    fprintf(stderr,ERROR PRODUCT_NOT_FOUND);
    return NULL;
}
Node* update_quantity (Node *root, char *name, int amount_to_update){
    /*
     * we the help of help to apdate we are apdating the sum
     * in case of failuir return null
     */
    if (!root){
        fprintf(stderr,ERROR);
        return root;
    }
    if (!name){
        fprintf(stderr,ERROR INVALID_POINTER);
        return root;
    }
    int sign =0;
    if (amount_to_update >0){
        help_to_update(root,root,name,amount_to_update,sign);
        return root;

    }
    else if (amount_to_update <0){
        sign =1;
        help_to_update(root,root,name,amount_to_update,sign);
        return root;
    }
    else {
        //we will do nothing because the amount to update is 0
        return root;
    }

}

/*
 * built the tree
 */
Node *build_bst (const char *filename) {
    char buffer[MAX];
    FILE *fpdr;
    fpdr = fopen(filename, "r");
    if (!fpdr) {
        fprintf(stderr, ERROR FILE_OPEN_FAILED);
        return NULL;
    }
    char s[MAX];
    char k[MAX];
    int quantity;
    int ind = 0;
    Node *root = NULL;
    while (fgets(buffer, MAX, fpdr)) {
        int i = 0;
        for (; buffer[i] != ':' && buffer[i] != '\n'; i += 1) {
            s[i] = buffer[i];
        }
        s[i] = '\0';
        i += 1;
        int j = 0;
        int not_int=0;
        for (; buffer[i] != '\n' && buffer[i]!='\r'; j += 1, i += 1) {
            k[j] = buffer[i];
            if (!isdigit(buffer[i]) && (buffer[i]!=' ')){
                not_int=NOT_INT;
            }
        }
        k[j] = '\0';
        if (!not_int) {
            quantity = strtol(k, NULL, 10);
            if (ind == 0) {
                root = create_root(root, s, quantity);
                ++ind;
            } else {
                add_product(root, s, quantity);
            }
        }
        else{
            add_product(root,s,0);
        } }
    fclose(fpdr);
    return root;
}
void delete_tree (Node *root) {
    /*
     * we the help of this func we are
     * deliting all the tree from the memory
     */
    if(root){
        delete_tree(root->left_child);
        delete_tree(root->right_child);
        free((root->product).name);
        free(root);
    }

}
Node *help_del_and_find_prev_last(Node *cur, char *name,\
int choose,int pr)
{    //this func help to do both thing
    // in case of choose =0 he
    // find the prev of the min of the root that are given
    if(!choose) {
        Node *prev = cur;
        int ind = 0;
        while (cur) {
            if (strcmp(cur->product.name, name) == 0)
            {
                if (pr==0){
                    return NULL;
                }
                return prev;
            }
            else if (strcmp(cur->product.name, name) > 0) {
                if (ind != 0) {
                    prev = cur;
                }
                cur = cur->left_child;
            }
            else if (strcmp(cur->product.name, name) < 0) {
                if (ind != 0) {
                    prev = cur;
                }
                cur = cur->right_child;
            }
            ind += 1;
            pr+=1;
        }
        return NULL;
    }
    else{
        while (cur->left_child->left_child) {
            cur = cur->left_child;
        }
        return cur;
    }}

void del_one_case(Node *cur, Node *prev, char ans) {
    /*
     * here we are deliting the name to delete in case of one child
     */
    if (cur->right_child) {
        if (ans == 'r') {
            prev->right_child = cur->right_child;
        } else {
            prev->left_child = cur->right_child;
        }
    } else {
        if (cur->left_child) {
            if (ans == 'l') {
                prev->left_child = cur->left_child;
            } else {
                prev->right_child = cur->left_child;
            }
        }

    }
}
Node *del_two(Node *cur, Node *prev, Node *prev_min,\
Node *min,Node *right_min, char s) {
/*
 *      * here we are deliting the name to delete in case of two child
 */
    if ((strcmp(min->product.name,\
    cur->right_child->product.name) != 0)) {
        if (prev && s == 'l') {
            prev->left_child = min;
        } else if (prev && s == 'r') {
            prev->right_child = min;
        }
        min->left_child = cur->left_child;
        min->right_child = cur->right_child;
        prev_min->left_child=right_min;
    }
    else if (strcmp(min->product.name,\
    cur->right_child->product.name) == 0) {
        if (s == 'l' && prev) {
            prev->left_child = cur->right_child;
        } else if (s == 'r' && prev) {
            prev->right_child = cur->right_child;
        }
        min->left_child=cur->left_child;
    }
    free(cur->product.name);
    free(cur);
    if (prev){
        return NULL;
    }
    return min;
}
int error(Node*root,char *name)
{
    /*
     * help to find error msg
     */

    if (!name) {
        fprintf(stderr, ERROR PRODUCT_NOT_FOUND);
        return 0;
    }
    if (!help_del_and_find_prev_last(root,\
    name, 0,1)) {
        fprintf(stderr, ERROR PRODUCT_NOT_FOUND);
        return 0;
    }
    return 1;
}
void help_case(Node*p,int s){
    /*
     * help dealing with 0 child case in the delete func
     */
    if (!s && p) {
        p->left_child = NULL;
    } else if (s && p) {
        p->right_child = NULL;
    }

}
Node *help_two_case(Node*p,Node*delete,\
Node*root,Node*prev_min,Node*right_min,Node*min,int s){
    /*
 * help dealing with two child case in the delete func
 */
    if (!p){
        if (s == 0 ) {
            return del_two(delete, p,\
            prev_min, min, right_min, 'l');            }
        {
            return del_two(delete, p,\
            prev_min, min, right_min, 'r');
        }
    }
    else if(p){
        if (s == 0 ) {
            del_two(delete, p, prev_min,\
            min, right_min, 'l');
            return root;
        }
        {
            del_two(delete, p, prev_min,\
            min, right_min, 'r');
            return root;
        }
    }
    return root;
}
Node *help_del_one(Node *delete,Node*p,Node*root,char leter)
{
    /*
 * help dealing with one child case in the delete func
 */
    del_one_case(delete, p, leter);
    free(delete->product.name);
    free(delete);
    return root;

}
/*
 * the next func delete  product from the tree
 */
void help_free(Node*root){
    free(root->product.name);
    free(root);
}
void call_help_case(Node *p,int s,Node *delete){
    /*
     * the other func is to long just help to less line
     */
    help_case(p,s);
    help_free(delete);
}
Node *call_help_case_two(Node *p,Node*delete){
    /*
     * the other func is to long just help to less line
     */
    p=delete->right_child;
    help_free(delete);
    return p;
}

Node *return_null(){
    fprintf(stderr, ERROR INVALID_POINTER);
    return NULL;
}
Node *delete_product(Node *root, char *name) {
    int s = 0, d = 0;
    if (!root) {
        return return_null();
    }
    if(!error(root,name)){
        return root;
    }
    Node *delete = NULL;
    if (strcmp(root->product.name, name) == 0) {
        if (!root->left_child->product.name && \
        !root->right_child->product.name) {
            help_free(root);
            return NULL;
        }
        delete = root;
        d = ROOT_DEL;
    }
    Node *p = help_del_and_find_prev_last(root, name,\
    0,0);
    if (!d) {
        if (strcmp(p->left_child->product.name, name) == 0) {
            delete = p->left_child;
        } else if ((strcmp(p->right_child->product.name, name) == 0)) {
            s = R;
            delete = p->right_child;
        }
    }if (!delete->left_child && !delete->right_child) {
        call_help_case(p,s,delete);
        return root;
    }
    if (delete->right_child && (!delete->left_child) && p) {
        return help_del_one(delete,p,root,'r');
    }
    else if (delete->right_child && (!delete->left_child)) {
        if (delete->right_child && !p) {
            return call_help_case_two(p,delete);
        }
    }
    if (delete->left_child && (!delete->right_child)) {
        return help_del_one(delete,p,root,'l');
    }
    Node *prev_min=NULL,*min=NULL;
    if (delete->right_child->left_child) {
        prev_min = help_del_and_find_prev_last(delete->right_child,\
        name, 1, 0);
        min = prev_min->left_child;
    }
    else{
        min = delete->right_child;
    }
    return help_two_case(p,delete,root,\
    prev_min,min->right_child,min,s);
}

