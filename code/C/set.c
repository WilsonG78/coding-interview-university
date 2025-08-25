#include<set.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

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
Node *inorderd_successor( Node *node){
    if(node->right){
        Node *curr = node->right;
        while(curr->left){
            curr = curr->left;
        }
        return curr;
    }
    Node *p = node->parent;
    Node *curr =node;
    while(p && curr == p->right){
        curr = p;
        p = p->parent;
    }
    return p;
}


//public
void insert_set(set *tree,int val){
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
                break;
            }
        }
        else if(curr->val >val){
            if(!curr->left){
                new_node->parent = curr;
                curr->left = new_node;
                break;
            }
        }
        else{
            free(new_node);
            curr =NULL;
        }
    }
    balance_tree(tree,new_node);
}
Node *min_in_subtree(Node *node){
    Node *curr = node;
    while(curr && curr->left){
        curr = curr->left;
    }
    return curr;
}

//public
int contains_set(set *tree , int val){
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
void delete_set(set *tree , int val){
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
    if(!curr) return;

    //case one
    Node *node_to_rebalance = NULL;
    if(!curr->right && !curr->left){
        node_to_rebalance = curr->parent;
        if(curr->parent){
            if(curr->parent->left == curr) curr->parent->left = NULL;
            else curr->parent->right =NULL;
        } 
        else{
            tree->root = NULL;
        }
        free(curr);
    }
    else if(!curr->left || !curr->right){
        Node *child = curr->left ? curr->left : curr->right;
        node_to_rebalance = curr->parent;
        if(curr->parent){
            if (curr->parent->left == curr) curr->parent->left = child;
            else curr->parent->right = child;
        } else {
            tree->root = child;
        }
        child->parent = curr->parent;
        free(curr);
    }
    else{
        Node *succ = min_in_subtree(curr->right);
        curr->val = succ->val;
        Node *child = succ->right;
        node_to_rebalance = succ->parent;
        if (succ->parent->left == succ) succ->parent->left = child;
        else succ->parent->right = child;
        if (child) child->parent = succ->parent;
        free(succ);
    }
    if(node_to_rebalance){
        balance_tree(tree,node_to_rebalance);
    }
}


//public
void init_set(set *tree) {
    tree->root = NULL;
}

//private
void free_subtree(Node *node) {
    if (node) {
        free_subtree(node->left);
        free_subtree(node->right);
        free(node);
    }
}

//public
void free_set(set *tree) {
    free_subtree(tree->root);
    tree->root = NULL;
}