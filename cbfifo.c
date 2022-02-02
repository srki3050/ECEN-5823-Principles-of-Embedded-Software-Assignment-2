#include <stdio.h>
#include <assert.h>
#include<string.h>
#include <stdint.h>
#include "cbfifo.h"
#define CAPACITY 128
uint8_t arr[CAPACITY];
uint8_t length = 0;
uint8_t read = 0; //initially read = 0
uint8_t write = 0;  //Initially write = 0
uint8_t is_full = 0;//Unable to create a boolean global variable, hence creating an uint8_t which is 1 byte of memory
/******************************************************************************************************************/
/*
* Enqueues the requested number of bits inside the buffer
* cannot enqueue on a full buffer
* If I cannot enqueue nbytes of buffer, I woul enqueue the best whatever I can
*/
size_t cbfifo_enqueue(void *buf, size_t nbyte){
    assert(buf!=NULL);
    assert(length <= CAPACITY);//Current elements present in the queue will always be less than CAPACITY
	if(nbyte < 0){
		return -1;
	}	
    assert((nbyte >= 0)&&(nbyte <= CAPACITY));//A limit on the incoming number of bytes
    if(length == CAPACITY){
        is_full = 1;
        return 0;
    }
    while(((length + nbyte) > CAPACITY)&&(nbyte >= 0)){
        nbyte--;
    }
    assert(buf!=NULL);
    uint8_t temp[nbyte];
    memcpy(temp,buf,nbyte);
    for(int i = 0;i < nbyte;i++){
        arr[((write+i) & (CAPACITY - 1))] = temp[i];
    }
    write = ((write + nbyte) & (CAPACITY - 1));
    length += nbyte;
    return nbyte;
}
/*******************************************************************************************************************/
/******************************************************************************************************************/
/*
* Dequeues the requested number of bits inside the buffer
* cannot Dequeue on a empty buffer
* If I cannot dequeue nbytes of buffer, I woul dequeue the best whatever I can
*/
size_t cbfifo_dequeue(void *buf, size_t nbyte){
    if(length == 0){
        return -1;
    }
    assert((length > 0)&&(nbyte >= 0)&&(nbyte <= CAPACITY));
    if((write == read)&&(is_full == 0)){
        return -1;
    }//Trying to dequeue from an empty queue.
    uint8_t temp[nbyte];
    for(int i = 0;i < nbyte;i++){
        temp[i] = arr[((read+i) & (CAPACITY - 1))];
    }
    memcpy(buf,temp,nbyte);
    read = ((read + nbyte) & (CAPACITY - 1));
    length-=nbyte;
    return nbyte;
}
/*
* Returns the number of elements currently available on the queue.
*/
size_t cbfifo_length(){
    return ((write - read) & (CAPACITY - 1));
}
/*
* Returns the Capacity
*/
size_t cbfifo_capacity(){
    return CAPACITY;
}
int main()
{
   return 0;
}