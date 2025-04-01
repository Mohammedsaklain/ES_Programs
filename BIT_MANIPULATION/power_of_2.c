/*Write a program to check if a number is a power of 2 or not*/
#include<stdio.h>
int main()
{
int a;
printf("enter a no");
scanf("%d",&a);
if(a && ((a & (a-1))==0))
  {
   printf("%d is a power of 2",a);
  }
else
  {
  printf("%d is not a power of 2",a);
  }
}
