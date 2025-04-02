/* Find the smallest power of 2 greater than or equal to a given number */

#include <stdio.h>
int Power_of_2(int P);

int main(void)
{
    printf("\n%d\n",Power_of_2(5));
    return 0;
}
int Power_of_2(int P)
{
    int Temp =1;
    while(Temp<P)
    {
        Temp = Temp *2;
    }
    return Temp;
}
