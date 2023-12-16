/*Write an Embedded C program to multiply any number by 2,3,9 in the fastest manner*/

#include<stdio.h>
int main()
{
    int num;
    printf("Enter number:");
    scanf("%d",&num);
    printf("3 X %d = %d\n",num, ((num<<1)+(num)));
    printf("2 x %d = %d\n", num, (num<<1));
    printf("9 X %d = %d\n",num, (num<<3)+num);
    return 0;
}
