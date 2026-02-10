/*
Write a C function that takes a pointer to a 32-bit unsigned integer representing a hardware register, 
a start bit position (0 to 31), an end bit position (0 to 31), and a value to set in that bit range. 
The function should:
1. Set the specified bit range (from start to end, inclusive) in the register to the given value.
2. Preserve all bits outside the specified range.
3. Return a status code: 0 for success, 1 if the bit range is invalid (e.g., start > end or end > 31), or 2 if the register pointer is NULL.
4. Ensure the value fits within the bit range (e.g., for a 3-bit range, value must be 0 to 7). Return 1 if the value is too large
*/

#include <stdio.h>
#include <stdint.h>

uint8_t bit_range(uint32_t * reg, uint8_t start_bit_pos, uint8_t end_bit_pos, uint32_t value);

int main(void) {
    uint32_t reg = 0;
    uint8_t SBP = 0, EBP = 1, value = 3, retval;
    retval = bit_range(&reg, SBP, EBP, value);
    if(retval==2){
        printf("Null register pointer\n");
    } else if(retval==1){
        printf("Invalid input range or value \n");
    } else if(retval==0){
        printf("successfully added \n");
    }
    return 0;
}

uint8_t bit_range(uint32_t * reg, uint8_t start_bit_pos, uint8_t end_bit_pos, uint32_t value)
{
    uint32_t clr_val = ((1U << (end_bit_pos - start_bit_pos + 1)) - 1);
    if(reg == NULL){
        return 2; /* NULL REG PTR */
    }
    if((start_bit_pos>=end_bit_pos) || end_bit_pos>31 || value > clr_val){
        return 1; /* INVALID RANGE*/
    } else {
        * reg &= ~(clr_val<<start_bit_pos);
        * reg |= (value<<start_bit_pos);
        return 0; /* SUCCESS */
    }
}
