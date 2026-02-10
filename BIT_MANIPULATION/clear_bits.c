/*
Write a C function that takes a pointer to a 32-bit unsigned integer representing 
a hardware register and an array of bit positions (each from 0 to 31) along with the array's size. 
The function should clear (set to 0) all the bits at the specified positions in the register 
and return the number of bits actually cleared. Ensure the function validates the bit positions, 
ignores invalid positions (outside 0 to 31), and modifies the register through the pointer. 
Use only standard C without any library functions beyond <stdint.h>
*/


#include <stdio.h>
#include <stdint.h>

uint8_t reset_bit(uint32_t * reg, uint32_t * arr_bit_pos, uint8_t size);

uint32_t reg1 = 15, clear_at[] = {0,1,2,40};
uint8_t arr_size = ((sizeof(clear_at))/(sizeof(clear_at[0]))), retval;

int main(void)
{
    retval = reset_bit(&reg1,clear_at,arr_size);
    printf("no of bits cleared = %u\n",retval);
    return 0;
}

uint8_t reset_bit(uint32_t * reg, uint32_t * arr_bit_pos, uint8_t size)
{
    uint8_t bits_cleared = 0;
    printf("original value = %u\n",*reg);
    if(size!=0){
        for(uint8_t i=0;i<size;i++){
            if(arr_bit_pos[i]<=31) {
                * reg&= ~(1<<arr_bit_pos[i]);
                bits_cleared+=1;
            }
        }
        printf("new value = %u\n",*reg);
        return bits_cleared;
    } else {
        return 0;
    }
    return 0;
}