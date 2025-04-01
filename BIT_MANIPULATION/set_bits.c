/* a function that takes an unsigned integer and returns the number of set bits (1s) in it*/

#include <stdio.h>
#include <stdint.h>

uint8_t NumOfSetBits(uint32_t InBit);

int main(void)
{
    printf("%hhu",NumOfSetBits(15));
}
uint8_t NumOfSetBits(uint32_t InBit)
{
    uint8_t Count= 0;
    for(uint8_t i=0;i<32;i++)
    {
        if((InBit) & (1<<i))
        {
            Count+=1;
        } 
    }
    return Count;
}