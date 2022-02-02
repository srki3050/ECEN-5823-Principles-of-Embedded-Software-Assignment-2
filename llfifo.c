#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "llfifo.h"
/***********************Node Structure*********************/
typedef struct element_s{
    void *element;
    struct element_s *next;
}element_t;
/************************Responsible for storing Capacity and Length Values and helps in creation of initial nodes********************************/
typedef struct llfifo_s{
    int length;
    int capacity;
    element_t* front;
    element_t* rear;
}llfifo_t;
/***********************Create Capacity********************/
/* Creates Capacity amount of nodes initially
*  While Operating withing this range of nodes, there is no need to malloc
*  While handling elements out of this range(Capacity). Need to Malloc while Enqueuing
*  If an element was dequeued from the queue, the incoming element is programmed to take its memory location but pointing to a different place
*/ 
llfifo_t *llfifo_create(int capacity){
    assert(capacity >= 0);
    llfifo_t *create = (llfifo_t *)malloc(sizeof(llfifo_t));//malloced 16 bytes of memory from heap.
    element_t *temp;
    create->capacity = capacity;
    create->length = 0;
    create->front = NULL;
    create->rear = NULL;
    for(int i = 0;i < capacity;i++){
        element_t *create_nodes = (element_t *)malloc(sizeof(element_t));
        if(i == 0){
            create->front = create_nodes;
            create->rear = create_nodes;
            temp = create_nodes;
        }
        else{
            temp->next = create_nodes;
            temp = create_nodes;
        }
        temp->next = NULL;
    }
    return create;
}
/***************************Enqueue Operation************************/
/* Enequeues the FIFO with a new element
*  Enqueue operations happen at the Rear end
*  The length is incremented by 1 each time a FIFO is enqueued.
*  When length exceeds original capacity, both length and capacity are programmmed to increase by 1
*/
int llfifo_enqueue(llfifo_t *fifo, void *element){
    assert(fifo->capacity >= 0);
    assert(fifo->length >= 0);
	assert(element!=NULL);
    if(fifo->length < fifo->capacity){
        if(fifo->length == 0){
            fifo->rear->element = element;
            fifo->length++;
        }
        else{
            fifo->rear = fifo->rear->next;
            fifo->rear->element = element;
            fifo->length++;
        }    
    }
    else{
        printf("Length Exceeds Capacity\n");
        element_t *createnode = (element_t *)malloc(sizeof(element_t));
        createnode->element = element;
        createnode->next = NULL;
        if((fifo->front == NULL)&&(fifo->rear == NULL)){
            printf("Queuesize is empty\n");
            fifo->front = createnode;
            fifo->rear = createnode;
        }
        else{
            printf("Queuesize is not empty - Memory Allocated for the new member\n");
            fifo->rear->next = createnode;
            fifo->rear = createnode;
            fifo->rear->element = element;
        }
        fifo->capacity++;
        fifo->length++;
    }
    return fifo->length;
}
/****************************Dequeue Operation***********************/
/* Dequeeus the element located in the front of the FIFO
*  The element is cleared and delinked from the queue
*  However, its memory is programmed to be used by the next incoming element from the rear end in the queue.
*  No memory is freed in this operation
*/
void *llfifo_dequeue(llfifo_t *fifo){
    element_t *tempvarR = fifo->rear->next;
    element_t *tempvarF = fifo->front->next;
    void * ret = fifo->front->element;
    fifo->front->element = NULL;
    fifo->rear->next = fifo->front;
    fifo->front->next = tempvarR;
    if(tempvarR == NULL){
        fifo->front->next = NULL;
    }
    fifo->front = tempvarF;
    fifo->length--;
    return ret;
}
/***************************Check length*****************************/
/*Prints the current length of the FIFO
*Increments by 1 on Enqueue and Decrements by 1 on Dequeue
*/
int llfifo_length(llfifo_t *fifo){
    return fifo->length;
}/************************Check capacity*****************************/
/*Prints the current length of the FIFO
*Increments by 1 on enqueue along with length if length exceeded capacity.
*/
int llfifo_capacity(llfifo_t *fifo){
    return fifo->capacity;
}
/***************************Destroy the Queue***********************/
/*Destroys the memeory created so far
*FIFO cannot be used after this again*/
void llfifo_destroy(llfifo_t *fifo){
    element_t *temp = fifo->front;
    while(temp->element!=NULL){
        free(temp);
        temp = temp->next;
    }
    fifo->front = NULL;
}
/*******************************************************************/
int main()
{
    return 0;
}
