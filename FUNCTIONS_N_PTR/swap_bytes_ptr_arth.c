/* Swap Bytes with pointer arithmetic */
/* Write a function swap_bytes that takes a pointer to a uint16_t variable. 
The function should reverse the byte order of the value pointed to by the pointer. 
For example, if the value is 0xABCD, the function should modify it to 0xCDAB.
The solution should use a pointer to an uint8_t and perform the swap using pointer arithmetic and temporary variables.
This is a common operation in embedded systems when dealing with data from different architectures or communication protocols 
(e.g., converting between big-endian and little-endian)*/


#include <stdio.h>
#include <stdint.h>

void swap_bytes(uint16_t * HalfWord);

int main(void){
    uint16_t s = 0xABCD;
    printf("Original Bytes = %X\n",s);
    swap_bytes(&s);
    printf("Swapped Bytes = %X\n",s);
    return 0;
}

void swap_bytes(uint16_t * HalfWord){
    uint8_t * byte_cnt = (uint8_t *)HalfWord;
    uint8_t temp;
    temp = byte_cnt[1];
    byte_cnt[1] = byte_cnt[0];
    byte_cnt[0] = temp;
}

