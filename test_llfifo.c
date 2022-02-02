#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "llfifo.h"
void test_llfifo(){
 /*************************************First Instance*****************************************************/
    llfifo_t *myfifo1 = llfifo_create(5);    //LEN = 0, CAP = 0
    assert(llfifo_capacity(myfifo1)==5);
    assert(llfifo_length(myfifo1)==0);   
    llfifo_enqueue(myfifo1,"Sleepy");        //Malloc Not Required LEN = 1, CAP = 5
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==5);
    assert(llfifo_length(myfifo1)==1);      
    llfifo_enqueue(myfifo1,"Grumpy");        //Malloc Not Required LEN = 2, CAP = 5
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==5);
    assert(llfifo_length(myfifo1)==2);
    llfifo_enqueue(myfifo1,"Sneezy");       //Malloc Not Required LEN = 3, CAP = 5
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==5);
    assert(llfifo_length(myfifo1)==3);
    llfifo_enqueue(myfifo1,"Bashful");      //Malloc Not Required LEN = 4, CAP = 5
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==5);
    assert(llfifo_length(myfifo1)==4);
    llfifo_enqueue(myfifo1,"Doc");          //Malloc Not Required LEN = 5, CAP = 5
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==5);
    assert(llfifo_length(myfifo1)==5);
    llfifo_enqueue(myfifo1,"Happy");        //Malloc Required LEN = 6, CAP = 6
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==6);
    assert(llfifo_length(myfifo1)==6);
    /*************Dequeue Operation****************************/
    assert(llfifo_dequeue(myfifo1)=="Sleepy"); //Malloc Required LEN = 5, CAP = 6
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==6);
    assert(llfifo_length(myfifo1)==5);
    /*************Enqueue Again********************/
    llfifo_enqueue(myfifo1,"Sleepy");       //Malloc Not Required LEN = 6, CAP = 6 - New Node takes the memory of the previously deleted node
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==6);
    assert(llfifo_length(myfifo1)==6);
    llfifo_enqueue(myfifo1,"Dopey");       //Malloc Required LEN = 7, CAP = 7
    display(myfifo1);
    assert(llfifo_capacity(myfifo1)==7);
    assert(llfifo_length(myfifo1)==7);
    /***********Destroy*****************/
    llfifo_destroy(myfifo1);
    llfifo_enqueue(myfifo1,"Another");  // Post destroy queue unfit to be used again
    assert(llfifo_capacity(myfifo1)==7);//No change in length or capacity
    assert(llfifo_length(myfifo1)==7); //Expected Assertion Failure here due to queue destroy
    /**********************************Second Instance********************************/
    llfifo_t *myfifo2 = llfifo_create(1);   //LEN = 0,CAP = 1
    llfifo_enqueue(myfifo2,"Sleepy");       //Malloc Not Required LEN = 1, CAP = 1
    display(myfifo2);
    assert(llfifo_capacity(myfifo2)==1);
    assert(llfifo_length(myfifo2)==1);
    llfifo_enqueue(myfifo2,"Dopey");       //Malloc Required LEN = 2, CAP = 2
    display(myfifo2);
    assert(llfifo_capacity(myfifo2)==2);
    assert(llfifo_length(myfifo2)==2);
    llfifo_enqueue(myfifo2,"Doc");       //Malloc Required LEN = 3, CAP = 3
    display(myfifo2);
    assert(llfifo_capacity(myfifo2)==3);
    assert(llfifo_length(myfifo2)==3);
    assert(llfifo_dequeue(myfifo2)=="Sleepy"); //Malloc Required LEN = 2, CAP = 3
    display(myfifo2);
    assert(llfifo_capacity(myfifo2)==3);
    assert(llfifo_length(myfifo2)==2);
    llfifo_enqueue(myfifo2,"Bashful");       //Malloc Not Required LEN = 3, CAP = 3
    display(myfifo2);
    assert(llfifo_capacity(myfifo2)==3);
    assert(llfifo_length(myfifo2)==3);
    /**********************************Third Instance*********************************/
    llfifo_t *myfifo3 = llfifo_create(0);   //LEN = 0,CAP = 0
    llfifo_enqueue(myfifo3,"Sleepy");       //Malloc Required LEN = 1, CAP = 1
    display(myfifo3);
    assert(llfifo_capacity(myfifo3)==1);
    assert(llfifo_length(myfifo3)==1);
    llfifo_enqueue(myfifo3,"Dopey");       //Malloc Required LEN = 2, CAP = 2
    display(myfifo3);
    assert(llfifo_capacity(myfifo3)==2);
    assert(llfifo_length(myfifo3)==2);
    llfifo_enqueue(myfifo3,"Doc");       //Malloc Required LEN = 3, CAP = 3
    display(myfifo3);
    assert(llfifo_capacity(myfifo3)==3);
    assert(llfifo_length(myfifo3)==3);
    assert(llfifo_dequeue(myfifo3)=="Sleepy"); //Malloc Required LEN = 2, CAP = 3
    display(myfifo3);
    assert(llfifo_capacity(myfifo3)==3);
    assert(llfifo_length(myfifo3)==2);
    llfifo_enqueue(myfifo3,"Happy");       //Malloc Not Required LEN = 3, CAP = 3
    display(myfifo3);
    assert(llfifo_capacity(myfifo3)==3);
    assert(llfifo_length(myfifo3)==3);
    /************************************************************************************/
}	