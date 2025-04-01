/* Implement a simple circular buffer (FIFO) for storing and retrieving bytes*/

/* 1. const uint8_t * PTR ---> You can change the pointer to point to different uint8_t values, 
                               but you cannot change the uint8_t value that the pointer currently points to. 
                               The data being pointed to is read-only through this pointer.*/

/* 2. uint8_t * const PRT ---> The pointer itself cannot be changed to point to a different memory location, 
                               but you can change the uint8_t value at the memory location the pointer points to.*/

#include <stdio.h>
#include <stdint.h>

#define CIRC_BUFF_MAC(x,y)      \
    uint8_t Max_Data_Len[y];    \
    circ_buff_str x = {         \
        .BUFF = Max_Data_Len,   \
        .head = 0,              \
        .tail = 0,              \
        .MaxLen = y             \
    }

typedef struct
{
    uint8_t * const BUFF;
    int head;
    int tail;
    const int MaxLen;
}circ_buff_str;

uint8_t circ_buff_push(circ_buff_str *SP, int data);
uint8_t circ_buff_pop(circ_buff_str *SP, uint8_t *data);

int main(void)
{
    return 0;
}

uint8_t circ_buff_push(circ_buff_str *SP, int data)
{
    uint8_t next;
    next = (SP->head)+1;    // Next where the Head will be pointed to 
    if(next>=SP->MaxLen)    // if the head reaches to Max Length of Buffer, Start from Initial Position of Buffer
    {
        next = 0;
    }
    if(next==SP->tail)      //If Head & Tail points to same(Means Buffer is Empty) Return from the Function
    {
        return -1;
    }
    SP->BUFF[SP->head] = data;
    SP->head= next;
    return 0;
}

uint8_t circ_buff_pop(circ_buff_str *SP, uint8_t *data)
{
    uint8_t next;
    next = (SP->tail)+1;
    
    if(next >= SP->MaxLen)  
    {
        next =0;
    }
    if(SP->head==SP->tail)  // If head & Tail is same, we don't have Data 
    {
        return -1;
    }
    *data = SP->BUFF[SP->tail]; // Read from Buffer & Push it to Buffer
    SP->tail = next;
    return 0;
}