/*Implement functions for addition, subtraction, and multiplication of two 16-bit fixed-point numbers with 8 fractional bits.*/

/*A.  In Q8.8 format, each number is stored in 16 bits:
    1. The upper 8 bits represent the integer part, and the lower 8 bits represent the fraction.
    2. We multiply by 256(2^8) to store fractional values in an integer representation.
    3. Addition and subtraction work like normal integers
    4. Multiplication results in Q16.16, so we shift back by 8 bits.
  B. Example: 5.75
    1. (5*256) + (0.75*256) = 1472  OR 5.75 * 256 = 1472
*/

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FLOAT2FPA(x) ((int16_t)(round((x)*256)))   // Converting Float to Q8.8
#define FPA2FLOAT(x) ((float)(x)/256.0)   // Conversion from Q8.8 to Float

int16_t FPA_Add(int16_t A, int16_t B);
int16_t FPA_Sub(int16_t A, int16_t B);
int16_t FPA_Mul(int16_t A, int16_t B);

int main(void)
{
    int16_t A=FLOAT2FPA(2.2),B=FLOAT2FPA(3.1);
    printf("%f\n",FPA2FLOAT(FPA_Add(A,B)));
    printf("%f\n",FPA2FLOAT(FPA_Sub(A,B)));
    printf("%f\n",FPA2FLOAT(FPA_Mul(A,B)));
    return 0;
}

int16_t FPA_Add(int16_t A, int16_t B)
{
    int16_t Temp;
    Temp=A+B;
    return Temp;
}
int16_t FPA_Sub(int16_t A, int16_t B)
{
    int16_t Temp;
    Temp=A-B;
    return Temp;
}
int16_t FPA_Mul(int16_t A, int16_t B)
{
    int32_t Temp;
    Temp=(int32_t)A*(int32_t)B;
    Temp=(Temp)>>8;
    return Temp;
}