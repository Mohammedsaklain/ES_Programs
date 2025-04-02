/*Implement a function to reverse the bits*/

#include <stdio.h>
#include <stdint.h>

uint32_t BitRev(uint32_t InBit);
int main(void)
{
    //45  00101101
    //180 10110100
    printf("%u",BitRev(500));
    return 0;
}

uint32_t BitRev(uint32_t InBit)
{
    uint32_t Temp1 =0;
    for(uint8_t i=0;i<32;i++)
    {
        if(InBit & (1<<i))  // Finding out of 1's 
        {
            Temp1 = Temp1 | (1<<(31 - i));
        }
    }
    return Temp1;
}
