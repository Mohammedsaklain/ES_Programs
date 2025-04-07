/* Define a structure with packed bitfields for a device register*/

#include <stdio.h>
#include <stdint.h>

typedef struct __attribute__((packed))  // Ensures No Padding – __attribute__((packed))
{
    uint8_t R0: 4;
    uint8_t R1: 4;
}Device_Reg1;

int main(void)
{
    Device_Reg1 B1 = { .R0 = 12, .R1 = 10};
    printf("%hhu %hhu",B1.R0,B1.R1);
    return 0;
}
