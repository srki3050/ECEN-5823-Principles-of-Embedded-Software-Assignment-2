#include <stdio.h>
#include <assert.h>
#include<string.h>
#include <stdint.h>
#include "cbfifo.h" 

void test_cbfifo(){
 /*************************Happy Cases**********************************/
   /**************basic happy case Scenario - Enqueue*********************/ 
   //Enqueue 2 items and ensure the Cbfifo is enqueuing both.
	char a[4] = "Read";
	assert(cbfifo_enqueue(a,4)==4);//Enqueue some bytes of String
	int b = 310;//Enqueue an int
	assert(cbfifo_enqueue(&b,112)==112);
	//Check for the length and check if write pointer moved forward by (length) bytes
	assert((cbfifo_length()==116));
	assert(write == 116);
   /**************basic happy case Scenario - dequeue*********************/
   char c[4];
   assert(cbfifo_dequeue(c,4)==4);//dequeue the characters sent upfront
   assert(strcmp(c,"Read")==0);//Check if you got back the same string
   int d = 0;
   assert(cbfifo_dequeue(&d,4)==4);
   assert(b == d);
   assert(cbfifo_length()==108);
   assert(read == 8);
   /*****************************Ciruclar Queue Wrap Around Case***************************/
   int e = 620;
   assert(cbfifo_enqueue(&e,16)==16);//buffer wraps around.
   /****************************Edge Cases***********************************************/
   int f = 450;
   assert(cbfifo_enqueue(&f,4)==4);
   /************************At this point the buffer is full*****************************/
   int g = 1;
   assert(cbfifo_enqueue(&g,1)==0); //This will fail since queu is full
   assert(cbfifo_enqueue(&g,1)==0); //This will pass since queue is full
   int h = 0;
   assert(cbfifo_dequeue(&h,3)==3);
   //printf("%ld",cbfifo_enqueue(&g,4)); //Length  = 125, hence you can add only 3 bytes before the queue is full, hence this returns the value 3
   char i[128];
   assert(cbfifo_dequeue(i,128));
   /*****************At this instant queue is empty***************/
   int j = 0;
   assert(cbfifo_dequeue(&j,1));//This will fail since queue is empty
   assert(cbfifo_dequeue(&j,0));//This will pass
   assert(cbfifo_enqueue(NULL,3));//Also this will fail since you cant enqueue a NULL pointer
} 