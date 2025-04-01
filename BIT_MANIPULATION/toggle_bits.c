//program to toggle a specific bit in a given register

#include<stdio.h>
unsigned char toggle(unsigned char reg,int pos)
{
    return reg ^ (1<<pos);
}
int main()
{
    unsigned char Register = 0b00001000;
    int position = 3;
    printf("Original Register 0x%X\n",Register);
    printf("Toggled Register 0x%X",toggle(Register,position));
    return 0;
}
