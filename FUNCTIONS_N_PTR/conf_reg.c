/* 
Write a C function that takes a pointer to a 32-bit unsigned integer 
representing a hardware register and a configuration structure containing 
two bit fields: a 2-bit field for a mode setting (values 0 to 3) and a 1-bit field for an enable flag. 
The function should update the register by setting bits 0 and 1 to the mode value and bit 2 to the enable flag, 
leaving all other bits unchanged. The function should return a status code: 0 for success,
1 if the mode value is invalid (outside 0 to 3), or 2 if the register pointer is NULL.
Use only standard C without any library functions beyond <stdint.h>
*/

#include <stdio.h>
#include <stdint.h>

typedef struct 
{
    uint8_t mode:           2;  /* bit 0-1 */
    uint8_t enable_flag:    1;  /* bit 2   */
} conf_reg1;    

uint8_t update_reg(uint32_t * reg, conf_reg1 * str);


int main(void)
{
    uint32_t  GP_reg = 0;            // GP register
    conf_reg1 GP_conf = {3,0};       // GP register configuration
    int retval;
    
    retval = update_reg(&GP_reg,&GP_conf);
    printf("return value = %u\n",retval);
    return 0;
}

uint8_t update_reg(uint32_t * reg, conf_reg1 * str)
{
    printf("original = %u\n",*reg); /* only for debug purpose */
    if((str->mode)>3) {
        return 1;
    } 
    if (reg == NULL) {
        return 2;
    } else {
        * reg &= ~(7<<0);
        * reg |= (((str->enable_flag)<<2) | (str->mode));
        printf("modified = %u\n",*reg); /* only for debug purpose */
        return 0;
    }
}