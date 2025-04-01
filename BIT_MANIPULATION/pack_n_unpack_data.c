/*To pack and unpack the data of 4 bits in single 32bit integer */

#include <stdio.h>
#include <stdint.h>

void pack(uint8_t Data, uint8_t Reg);
uint8_t unpack(uint8_t Reg);

struct storage Sector1;

struct storage
{
    uint32_t Bank1; // 0000 0000 0000 0000 0000 0000 0000 0000
                    // R7   R6   R5   R4   R3   R2   R1   R0
};

int main(void)
{
    uint8_t a,b;
    char D;
    while(1)
    {
        printf("Pack(P) or Unpack(U)\n");
        scanf(" %c",&D); // Given space before reading character, bcz to skip any leading whitespace or newlines before reading the character 
        if(D=='P')
        {
            printf("Enter data to pack, With Reg(0-7)\n");
            scanf("%hhu%hhu",&a,&b);    // %hhu is correct format specifier for uint8_t:
                                        // uint8_t is treated as unsigned character by Gcc but %u expects unsigned int, so if used get's warning
            pack(a,b);
        }
        else if (D=='U')
        {
            printf("Enter which Reg(0-7) Data\n");
            scanf("%hhu",&b);
            printf("%hhu\n",unpack(b));
        }
        else{
            printf("Not correct Command\n");
        }
    }
    
    return 0;
}
void pack(uint8_t Data, uint8_t Reg)
{
    Sector1.Bank1|= (Data<<(Reg*4));
}
uint8_t unpack(uint8_t Reg)
{
    uint8_t Temp =0;
    Temp = (Sector1.Bank1>>(Reg*4))&0x0F;
    return Temp;
}
