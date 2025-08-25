#include <stack_vector.h>
//public
void init_stack_stack_vector(stack_vector *stack_vector, int init_capacity){
    if(stack_vector->data) return; 
    if(init_capacity <= 0) return;
    stack_vector->size = 0;
    stack_vector->capacity = init_capacity;
    stack_vector->data = (int)malloc(init_capacity);
}

//public
void push(stack_vector *stack_vector,int num){
    if(stack_vector->capacity == stack_vector->size){
        stack_vector->capacity = 2 * stack_vector->size;
        stack_vector->data = (int)realloc(stack_vector->data,stack_vector->capacity);
    }
    stack_vector->data[stack_vector->size] = num;
    stack_vector->size += 1;
}
//public
int size(stack_vector *stack_vector){
    return stack_vector->size;
}
//public
int capacity(stack_vector *stack_vector){
    return stack_vector->capacity;
}
//public
int is_empty(stack_vector *stack_vector){
    return stack_vector->size == 0;
}
//public
int at(stack_vector *stack_vector, int index){
    if(index >= stack_vector->size){
        return -1;
    }
    return stack_vector->data[index];
}
//public
void insert(stack_vector *stack_vector,int index, int iteam){
    if( index  > stack_vector->size){
        return;
    }
    if(stack_vector->capacity == stack_vector->size){
        stack_vector->capacity *= 2;
        stack_vector->data = (int)realloc(stack_vector->data , stack_vector->capacity);
    }
    int tmp = stack_vector->data[index];
    int tmp2;
    stack_vector->data[index] = iteam;
    stack_vector->size +=1;
    for(int i=index +1; i <stack_vector->size; i++){
        tmp2 = stack_vector->data[i] ;
        stack_vector->data[i] = tmp;
        tmp = tmp2;
    }
}

//public
int pop(stack_vector *stack_vector){
    if(!stack_vector) return NULL;
    int res = stack_vector->data[stack_vector->size];
    stack_vector->size -=1;
    if(2 * stack_vector->size < stack_vector->capacity){
        stack_vector->capacity = stack_vector->size +1;
        stack_vector->data = (int)realloc(stack_vector->data,stack_vector->capacity);
    }
    return res;
}

//public
int find(stack_vector *stack_vector, int iteam){
    for(int i =0 ; i < stack_vector->size ; i++){
        if(stack_vector->data[i] == iteam) return i;
    }
    return -1;
}
//public
void resize(stack_vector *stack_vector, int new_capacity){
    if(stack_vector->capacity == stack_vector->size){
        if(new_capacity <= stack_vector->capacity){
            stack_vector->capacity *= 2;
            
        }
        else{
            stack_vector->capacity = new_capacity;
        }
        stack_vector->data = (int)realloc(stack_vector->data,stack_vector->capacity);
    }
    else if(stack_vector->capacity >= stack_vector->size){
        if(new_capacity >= stack_vector->capacity){
            stack_vector->capacity /= 2;
            
        }
        else{
            stack_vector->capacity = new_capacity;
        }
        stack_vector->data = (int)realloc(stack_vector->data,stack_vector->capacity);
    }
}