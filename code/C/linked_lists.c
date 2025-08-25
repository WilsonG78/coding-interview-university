#include <linked_list.h>

void init_list(LinkedList *list){
    list->size = 0;
    list->head = list->tail = NULL;
}

void free_list(LinkedList *list){
    while (list->head)
    {
        pop_front(list);
    }
    free(list);
}

int size(LinkedList *list){
    return list->size;
}

int empty(LinkedList *list){
    return list->size == 0; 
}

int value_at(LinkedList *list , int index){
    if(index >= list->size) return -1;
    Node *curr = list->head;
    for(int i =0 ; i < index; i++){
        curr = curr->next;
    }
    return curr->data;
}

void push_front(LinkedList *list , int value){
    Node *new_head = (Node*)malloc(sizeof(Node));

    new_head->data = value;
    new_head->next = list->head;
    list->head = new_head;
    list->size +=1;
    if(list->size ==1) list->tail = new_head;
}

int pop_front(LinkedList *list){
    if(!list->head) return -1;
    Node *newhead = list->head->next;
    Node *toDelete = list->head;
    list->head = newhead;
    int res = toDelete->data;
    free(toDelete);
    list->size -=1;
    if(list->size == 1) list->tail = NULL;
    return res;
}

void push_back(LinkedList *list , int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = value;
    if(list->size == 0){
        list->head = newNode;
        list->tail = newNode;
        list->size +=1;
        return;
    }
    list->tail->next =newNode;
    list->tail  = newNode;
    list->size +=1;
}

int pop_back(LinkedList *list){
    if (list->size == 0) return -1;
    int res;
    if(list->size == 1) {
        int res = list->tail->data;
        free(list->tail);
        list->head = list->tail = NULL;
        list->size = 0;
        return res;
    }
    Node *curr = list->head;
    for(int i =0 ; i <list->size -2 ; i++){
        curr= curr->next;
    }
    int res = list->tail->data;
    free(list->tail);
    list->tail =curr;
    list->tail->next = NULL;
    list->size -=1;
    return res;
}

int front(LinkedList *list) {
    if(list->size == 0) return -1;
    return list->head->data;
}
int back(LinkedList *list){
    if(list->size == 0) return -1;
    return list->tail->data;
}

void insert(LinkedList *list , int index, int value) {
    if(index < 0 || index > list->size) return;
    if(index == 0 ) {push_front(list,value); return;}
    if(index == list->size) {push_back(list,value); return;}
    Node *curr = list->head;
    for(int i =0 ; i < index -1 ; i++){
        curr = curr->next;
    }
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = curr->next;
    curr->next = newNode;
    list->size +=1;
}

int erase(LinkedList *list , int index){
    if(index < 0 || index >=list->size) return -1;
    if(index == 0) return pop_front(list);
    if(index == list->size-1) return pop_back(list);
    
    Node *curr = list->head;
    for(int i =0 ; i< index -1; i++) {
        curr = curr->next;
    }
    Node *toDelete = curr->next;
    int res = toDelete->data;
    curr->next = toDelete->next;
    free(toDelete);
    list->size -=1;
    return res;
}

int value_n_from_end(LinkedList *list,int n){
    if(n > list->size -1) return -1;
    int index = list->size - 1 - n;
    Node *curr=  list->head;
    for( int i =0 ; i  <index ; i++){
        curr = curr->next;
    }
    return curr->data;
}

void reverse(LinkedList *list) { 
    if(list->size <= 1 ) return;
    Node *prev = NULL;
    Node *curr = list->head;
    Node*next = NULL;

    list->tail = list->head;
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev =curr;
        curr = next;
    }
    list->head = prev;
}

void remove_value(LinkedList *list , int value){
    if(list->head == NULL) return;

    if(list->head->data == value) {
        pop_front(list);
        return;
    }
    Node *curr = list->head;
    while(curr->next != NULL && curr->next->data == value){
        curr = curr->next;
    }
    if(curr == NULL) return;
    Node *toDelete = curr->next;
    curr->next = toDelete->next;
    if(toDelete == list->tail) list->tail = curr;curr->next = NULL;
    free(toDelete);
    list->size -=1;
}


int main(){
    LinkedList list ={0}, *listP;
    listP = &list;
    init_list(listP);
    for(int i =0 ; i < 6 ; i++){
        push_back(listP,i);
    }
    for(int i =0 ; i < 10 ; i++) {
        push_front(listP,i);
    }
    
    reverse(listP);
    Node *curr= listP->head;
    for(int i=0; i < listP->size; i++){
        printf("Index: %d Value: %d \n" ,i,curr->data );
        curr= curr->next;
    }
    while(!empty(listP)) {
        pop_front(listP);
    }
}