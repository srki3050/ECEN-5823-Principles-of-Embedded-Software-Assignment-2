# ECEN-5823-Principles-of-Embedded-Software-Assignment-2
Assignment 2 FIFO two ways
Part 1 - llfifo
1. Uses linked list method of queue
    Logic
      1. Create Capacity amount of nodes initially
      2. In case if the length exceeds capacity create new nodes for every incoming elements
      3. While Dequeueing, Remove the node, delink it from the list and then use the same memory to hold the next incoming element
      4. Point it to the rear->next node.
      5. Do not free the memory until FIFO is destroyed
      6. The queue cannot be used post destroyal.
2. Uses Array on Circular Buffer of queue
      1. Create an array to hold capacity amount of elements
      2. start with write and read  = 0
      3. Start increasing the write pointer by number of bytes you are enqueuing in every operation.
      4. Start increasing the read pointer by number of bytes you are dequeuing in every operation.
      5. If you can deliver 3bytes of data into the buffer but the caller asks for 4 bytes of data. Facilitate 3
      6. Do not allow enqueue on a full buffer
      7. Do not allow dequeue on an empty buffer

Test Conditions tested for both the function including border conditions.
