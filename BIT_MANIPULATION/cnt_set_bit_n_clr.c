/*
Write a C function that takes a pointer to a 32-bit unsigned integer representing an interrupt status register 
and an array of interrupt flag positions (each from 0 to 31) along with the array's size. The function should:
Count the number of pending interrupts (bits set to 1) at the specified positions in the register.
Clear those interrupt flags by setting the corresponding bits to 0.
Return the count of pending interrupts found.
The function should ignore invalid bit positions (outside 0 to 31), modify the register through the pointer, 
and handle NULL pointers or invalid array sizes gracefully by returning 0 without modifying the register.
 Use only standard C without any library functions beyond <stdint.h>
*/

#include <stdio.h>
#include <stdint.h>

uint8_t clear_intr(uint32_t * status_reg_int, uint8_t * flag_int_pos, uint8_t size);

int main(void) {
    uint32_t GP_Reg     = 15U;
    uint8_t Flag_Pos[] = {0,1,2,32};
    uint8_t Size = ((sizeof(Flag_Pos))/(sizeof(Flag_Pos[0]))), retval;
    retval = clear_intr(&GP_Reg, Flag_Pos, Size);
    printf("The return value = %u\n",retval);
    return 0;
}

uint8_t clear_intr(uint32_t * status_reg_int, uint8_t * flag_int_pos, uint8_t size){
    uint8_t pending_int = 0;            // To store the no of pending interrupts
    if(size>32){
        return 0;
    }
    if((status_reg_int==NULL) || (flag_int_pos==NULL)){
        return 0;
    }
    for(uint8_t i=0;i<size;i++){
        if(flag_int_pos[i]<32){
            if(((*status_reg_int)>>flag_int_pos[i]) & 1U){
                * status_reg_int &= ~(1U<<flag_int_pos[i]);
                pending_int++;
            }
        }
    }
    return pending_int;
}