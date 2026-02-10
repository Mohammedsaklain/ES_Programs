/* volatile & Data Structures */

/* 1. Define a struct named LedRegister that contains two bit-fields: enabled (1 bit) and color (7 bits).
   2. In the main function, declare a variable of type LedRegister and initialize its fields to some values.
   3. Write a function set_led_state that takes a pointer to an LedRegister and two arguments: a uint8_t for the enabled state and a uint8_t for the color. 
   The function should update the corresponding fields in the struct using the bit-field access syntax (->).
   4. Finally, declare another variable of type LedRegister and apply the volatile keyword to it. Explain why this is important for a hardware register
*/

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t enabled : 1;
    uint8_t color   : 7;
} LedRegister;


void set_led_state (LedRegister * set_state, uint8_t EN_DIS, uint8_t color);

int main(void)
{
    LedRegister LED1;
    volatile LedRegister LED2;
    set_led_state(&LED1,0,6);
    printf("%d\n",LED1.enabled);
    printf("%d\n",LED1.color);
    return 0;
}

void set_led_state (LedRegister * set_state, uint8_t EN_DIS, uint8_t color){
    set_state->enabled    = EN_DIS;
    set_state->color      = color; 
}


