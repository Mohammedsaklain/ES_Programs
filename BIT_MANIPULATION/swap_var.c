/*How will you swap two variables? Write different approaches for the same*/

#include<stdio.h>
int main()
{
//Using Extra Memory Space:
int num1=20, num2=30, temp;
temp = num1;
num1 = num2;
num2 = temp;
  
  //Using Arithmetic Operators:
int num1=20, num2=30;
num1=num1 + num2;
num2=num1 - num2;
num1=num1 - num2;
  
  //Using Bit-Wise Operators:
int num1=20, num2=30;
num1=num1 ^ num2;
num2=num2 ^ num1;
num1=num1 ^ num2;
  
  //Using One-liner Bit-wise Operators:
int num1=20, num2=30;
num1^=num2^=num1^=num2;  
//The order of evaluation here is right to left.

  //Using One-liner Arithmetic Operators:
int num1=20, num2=30;
num1 = (num1+num2)-(num2=num1);
//Here the order of evaluation is from left to right.
}
