#define max(a,b) ((a) > (b) ? (a) : (b))
#include <stdlib.h>
#include <math.h>
typedef struct Node
{
    int val;
    Node *left;
    Node *right;
    Node *parent;
    int height;
}Node;

typedef struct set
{
    Node *root;

}set;



void update_height(Node *node){
    if( node){
        node->height  = max(node->left->height , node->right->height) +1;
    }
    
}

void update_height_upwards(Node *node) {
    while (node) {
        int left_h = node->left ? node->left->height : 0;
        int right_h = node->right ? node->right->height : 0;
        node->height = max(left_h, right_h) + 1;
        node = node->parent;
    }
}

void balance(set *tree , Node *node){
    if(abs(node->left->height - node->right->height) <2 ){
        return;
    }
    if(node->left->height - node->right->height >1){
        if(node->left->right->height > node->left->left->height){
           left_rotate(tree,node->left);
        }
        else{
            right_rotate(tree,node);
        }
        
    }
    else{
        if(node->right->left->height > node->right->right->height){
            right_rotate(tree,node->right);
        }
        else{
            left_rotate(tree,node);
        }
        
    }

}

void right_rotate(set *tree ,Node *node){
    
    Node *new_root = node->left;
    Node *tmp = new_root->right;

    new_root->right = node;
    node->left = tmp;

    new_root->parent = node->parent;
    node->parent = new_root;
    if(tmp) tmp->parent = node;

    if(new_root->parent){
        if(new_root->parent->left == node){
            new_root->parent->left = new_root;
        }
        else{
            new_root->parent->right = new_root;
        }
    }
    update_height(node);
    update_height(new_root);
    update_height_upwards(node->parent);

}

void left_rotate(set *tree ,Node *node){
    Node *new_root = node->right;
    Node *tmp = new_root->left;

    new_root->left = node;
    node->right = tmp;

    new_root->parent = node->parent;
    node->parent = new_root;
    if(tmp) tmp->parent = node;

    if(new_root->parent){
        if(new_root->parent->left == node){
            new_root->parent->left = new_root;
        }
        else{
            new_root->parent->right = new_root;
        }
    }
    update_height(node);
    update_height(new_root);
    update_height_upwards(node->parent);
}

void insert(set *tree,int val){
    Node *curr = tree->root;
    while(1){
        if( curr->val < val){
            if(!curr->right){
                Node *new_node = (Node*)malloc(sizeof(Node));
                new_node->parent = curr;
                new_node->height =1;
                new_node->val = val;
                curr->right = new_node;
                return;
            }
        }
        if(curr->val >val){
            if(!curr->left){
                Node *new_node = (Node*)malloc(sizeof(Node));
                new_node->parent = curr;
                new_node->height =1;
                new_node->val = val;
                curr->left = new_node;
                return;
            }
        }
        if(curr->val == val){
            return;
        }
    }
}

int contains(set *tree , int val){
    Node *curr = tree->root;
    while(curr){
        if(curr->val == val){
            return 1;
        }
        if(curr->val > val){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return 0;
}

