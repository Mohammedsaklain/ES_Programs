/* Implement a simple circular buffer (FIFO) for storing and retrieving bytes*/

/* 1. const uint8_t * PTR ---> You can change the pointer to point to different uint8_t values, 
                               but you cannot change the uint8_t value that the pointer currently points to. 
                               The data being pointed to is read-only through this pointer.*/

/* 2. uint8_t * const PRT ---> The pointer itself cannot be changed to point to a different memory location, 
                               but you can change the uint8_t value at the memory location the pointer points to.*/