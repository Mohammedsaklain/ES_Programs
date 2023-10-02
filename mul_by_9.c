/*Write an Embedded C program to multiply any number by 9 in the fastest manner*/
#include<stdio.h>
void main(){
    int num;
    printf(“Enter number: ”);
    scanf(“%d”,&num);
    printf(“%d”, (num<<3)+num);
}
