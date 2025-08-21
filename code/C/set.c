#include <stdlib.h>
#include <math.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int height;
}Node;

typedef struct set
{
    Node *root;

}set;

//private
Node* init_node( int val , Node *left , Node *right,Node *parent){
    Node *new_node = (Node *)malloc(sizeof(Node));
    if(!new_node){
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->val = val;
    new_node->left = left;
    new_node->right = right;
    new_node->parent = parent;
    int left_h = left ? left->height : 0;
    int right_h = right ? right->height : 0;
    new_node->height = (left_h > right_h ? left_h : right_h) + 1;
    return new_node;
}

//private
void update_height(Node *node){
    if( node){
        int left_h = node->left ? node->left->height : 0;
        int right_h = node->right ? node->right->height : 0 ;
        node->height  = max(left_h,right_h) +1;
    }
    
}

//private
void update_height_upwards(Node *node) {
    while (node) {
        int left_h = node->left ? node->left->height : 0;
        int right_h = node->right ? node->right->height : 0;
        node->height = max(left_h, right_h) + 1;
        node = node->parent;
    }
}
//private
void balance_node(set *tree , Node *node){
    int left_h = node->left ? node->left->height : 0;
    int right_h = node->right ? node->right->height : 0;

    if(abs(left_h - right_h) <2 ){
        return;
    }
    if(left_h - right_h >1){
        int left_right_h = node->left->right ? node->left->right->height : 0;
        int left_left_h = node->left->left ? node->left->left->height : 0;

        if(left_right_h > left_left_h){
           left_rotate(tree,node->left);
        }
        else{
            right_rotate(tree,node);
        }
        
    }
    else{
        int right_left_h = node->right->left ? node->right->left->height : 0;
        int right_right_h = node->right->right ? node->right->right->height : 0;

        if(right_left_h > right_right_h){
            right_rotate(tree,node->right);
        }
        else{
            left_rotate(tree,node);
        }  
    }

}

//private
void balance_tree(set *tree, Node *node){
    while (node)
    {
        update_height(node);
        balance_node(tree,node);
        node = node->parent;
    }
    
}
//private
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
    }else{
        tree->root = new_root;
    }
    update_height(node);
    update_height(new_root);

}
//private
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
    }else{
        tree->root = new_root;
    }
    update_height(node);
    update_height(new_root);
}
//private
Node *next_node_in_post_order(set *tree , Node *node){
    if(node->right){
        Node *curr = node->right;
        while(curr->left){
            curr = curr->left;
        }
        return curr;
    }
}


//public
void set_insert(set *tree,int val){
    Node *curr = tree->root;
    Node *new_node = init_node(val,NULL,NULL,NULL);
    if(!curr){
        tree->root = new_node;
        return;
    }
    while(curr){
        if( curr->val < val){
            if(!curr->right){
                new_node->parent = curr;
                curr->right = new_node;
                curr = NULL;
            }
        }
        else if(curr->val >val){
            if(!curr->left){
                new_node->parent = curr;
                curr->left = new_node;
                curr = NULL;
            }
        }
        else{
            free(new_node);
            curr =NULL;
        }
    }
    balance_tree(tree,new_node);
}
//public
int set_contains(set *tree , int val){
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

//public
//TODO
void set_delete(set *tree , int val){
    Node *curr = tree->root;
    while(curr){
        if(curr->val  > val){
            curr= curr->left;
        }
        else if(curr->val < val){
            curr = curr->right;
        }
        else{
            break;
        }
    }
    if(curr){
        if(curr->right && curr->left){
            Node *post_order = next_node_in_post_order(tree,curr);
            curr->val = post_order->val;
            if(post_order->parent->left == post_order){
                post_order->right = post_order->parent->left;
                post_order->right->parent = post_order->parent;
                free(post_order);
            }
        }
    }
}