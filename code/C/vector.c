#include <stdio.h>
#include <stdlib.h>


typedef struct Vector
{
    int size;
    int capacity;
    int *data;
} Vector;

void init_vector(Vector *vector, int init_capacity){
    if(vector->data) return; 
    if(init_capacity <= 0) return;
    vector->size = 0;
    vector->capacity = init_capacity;
    vector->data = (int)malloc(init_capacity);
}


void push(Vector *vector,int num){
    if(vector->capacity == vector->size){
        vector->capacity = 2 * vector->size;
        vector->data = (int)realloc(vector->data,vector->capacity);
    }
    vector->data[vector->size] = num;
    vector->size += 1;
}

int size(Vector *vector){
    return vector->size;
}

int capacity(Vector *vector){
    return vector->capacity;
}

int is_empty(Vector *vector){
    return vector->size == 0;
}

int at(Vector *vector, int index){
    if(index >= vector->size){
        return -1;
    }
    return vector->data[index];
}

void insert(Vector *vector,int index, int iteam){
    if( index  > vector->size){
        return;
    }
    if(vector->capacity == vector->size){
        vector->capacity *= 2;
        vector->data = (int)realloc(vector->data , vector->capacity);
    }
    int tmp = vector->data[index];
    int tmp2;
    vector->data[index] = iteam;
    vector->size +=1;
    for(int i=index +1; i <vector->size; i++){
        tmp2 = vector->data[i] ;
        vector->data[i] = tmp;
        tmp = tmp2;
    }

}

void prepend(Vector *vector, int iteam){
    if(vector->capacity == vector->size){
        vector->capacity *= 2;
        vector->data = (int)realloc(vector->data , vector->capacity);
    }
    int tmp = vector->data[0];
    int tmp2;
    vector->size +=1;
    for(int i =1 ; i < vector->size ; i++){
        tmp2 = vector->data[i];
        vector->data[i] = tmp;
        tmp = tmp2;
    }
}

int pop(Vector *vector){
    if(!vector) return NULL;
    int res = vector->data[vector->size];
    vector->size -=1;
    if(2 * vector->size < vector->capacity){
        vector->capacity = vector->size +1;
        vector->data = (int)realloc(vector->data,vector->capacity);
    }
    return res;
}

void delete(Vector *vector, int index){
    if(index >= vector->size) return ;
    int tmp , tmp2 = vector->data[vector->size-1];
    for(int i =vector->size - 1; i > index ; i--){
        tmp = vector->data[i-1];
        vector->data[i-1] = tmp2;
        tmp2 = tmp;
    }
    vector->size -=1;
    if(4 * vector->size < vector->capacity){
        vector->capacity = 2 * vector->size ;
        vector->data = (int)realloc(vector->data,vector->capacity);
    }
}

void remove(Vector *vector,int iteam){
    int i =0 ;
    int p = 0;
    while(i < vector->size){
        if(vector->data[i] == iteam){
            p +=1;
            vector->size -=1;
        }
        vector->data[i] = vector->data[i+p];
        i++;
    }
    if(4 * vector->size < vector->capacity){
        vector->capacity = 2 * vector->size ;
        vector->data = (int)realloc(vector->data,vector->capacity);
    }
}

int find(Vector *vector, int iteam){
    for(int i =0 ; i < vector->size ; i++){
        if(vector->data[i] == iteam) return i;
    }
    return -1;
}

void resize(Vector *vector, int new_capacity){
    if(vector->capacity == vector->size){
        if(new_capacity <= vector->capacity){
            vector->capacity *= 2;
            
        }
        else{
            vector->capacity = new_capacity;
        }
        vector->data = (int)realloc(vector->data,vector->capacity);
    }
    else if(vector->capacity >= vector->size){
        if(new_capacity >= vector->capacity){
            vector->capacity /= 2;
            
        }
        else{
            vector->capacity = new_capacity;
        }
        vector->data = (int)realloc(vector->data,vector->capacity);
    }
}

int main(){
    Vector vector = {0};
}
