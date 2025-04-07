/*Create functions to set, clear, and read bits within the structure*/

#include <stdio.h>
#include <stdint.h>

uint8_t Set_Clr(uint8_t Bit, uint8_t Mode);
uint8_t Read(uint8_t Bit);

typedef struct
{
    uint16_t R0;
}BANK1;

volatile BANK1 A1;
int main(void)
{
    Set_Clr(4,1);
    printf("%u ", Read(4));
    printf("%u ", A1.R0);
    return 0;
}

/* Mode: 0->Clr, 1->Set
   Reg : R0, R1*/
uint8_t Set_Clr(uint8_t Bit, uint8_t Mode)
{
    if(Bit>15)
    {
        return 1;
    }
    if(Mode==0)
    {
        A1.R0&=~(1<<Bit);
    }
    else if(Mode==1)
    {
        A1.R0|=(1<<Bit);
    }
    else{
        return 1;
    }
    return 0;
}

uint8_t Read(uint8_t Bit)
{
    if(Bit>15)
    {
        return 0;
    }
    uint8_t Temp;
    Temp = (A1.R0>>Bit) & 0x01;
    return Temp;
}

