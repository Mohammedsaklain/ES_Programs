/* is_power_of_two  */


/* Write a C function called is_power_of_two that takes a single unsigned 32-bit integer (uint32_t) as an argument. 
The function should return 1 if the number is a power of two (e.g., 1, 2, 4, 8, 16, etc.) and 0 otherwise. 
You must not use any loops, recursion, or floating-point arithmetic. Use bit manipulation to solve this problem*/


#include <stdio.h>
#include <stdint.h>

uint8_t is_power_of_two (uint32_t Number);

int main(void){
    uint32_t No;
    while(1){
        printf("Enter a +ve Integer \n");
        
        if(scanf("%lu",&No) != 1){  // On success(when it takes correct %lu value) scanf returns 1, or else 0
            printf("Invalid Input, Please enter valid unsigned Integer\n");
            while(getchar()!='\n'); /* Read & discard the buffer */
            continue;
        }
        if(is_power_of_two(No)){
            printf("Power of 2\n");
        } else {
            printf("Not a power of 2\n");
        }
    }
    return 0;
}

uint8_t is_power_of_two (uint32_t Number)
{
    if(Number==0){
        return 0;
    } else {
        return (Number & (Number - 1)) == 0;
    }
}