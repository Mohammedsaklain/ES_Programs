/* unions - type punning */

/* 
Define a union named Register32Bit that has two members:
    1. A single uint32_t member named word.
    2. An array of four uint8_t members named bytes.
    3. In the main function, declare a variable of type Register32Bit.
    4. Set the word member to a specific hexadecimal value (e.g., 0xDEADBEEF).
    5. Then, without changing the word member, access and print the individual bytes from the bytes array to show that the union allows you to view the same memory in different ways.
*/

/* This challenge demonstrates how union can be used for type-punning and for breaking down multi-byte data into individual bytes, 
a common task in embedded systems when dealing with different endianness or low-level data manipulation. 
Type-punning is a programming technique that allows you to access the same memory location through different data types */

#include <stdio.h>
#include <stdint.h>

typedef union
{
    uint32_t word;
    uint8_t bytes[4];
} Register32Bit;

int main(void)
{
    Register32Bit GP;
    GP.word = 0xDEADBEEF;
    for(int i=0;i<4;i++){
        printf("%X\n",GP.bytes[i]);
    }
    return 0;
}


