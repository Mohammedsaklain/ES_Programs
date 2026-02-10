#include "debounce.h"
#include <stdio.h>

/**
 * @brief Sets the state of an LED. In this project, it simply controls bit 0 of the output register.
 */
void led_set(button_t *btn, uint8_t state){
    if(state){
        // Set bit 0 of the output register high
        *btn->output_reg |= (1 << 0);
    } else {
        // Set bit 0 of the output register low
        *btn->output_reg &= ~(1 << 0);
    }
    // Note: In a real application, we might want the LED pin to match the button pin,
    // in which case you would use btn->pin_mask here as well.
}

/**
 * @brief Initializes the button struct with necessary hardware and configuration info.
 */
void button_init(button_t * btn, const volatile uint32_t * input, volatile uint32_t * output, uint8_t pin_number){
    // *** CRITICAL FIX ***
    // Store the addresses of the hardware registers. Without this, the pointers
    // in the struct would be uninitialized, and dereferencing them in button_update
    // would cause a crash (Segmentation Fault).
    btn->input_reg = input;
    btn->output_reg = output;

    // Create the bitmask for the specified pin number.
    // This allows us to check only the relevant bit in the input register.
    if(pin_number <= 31){ // Ensure pin_number is valid for a 32-bit register
        btn->pin_mask = (1U << pin_number);
    }

    // Assume the button is released at the start.
    btn->prev_stable_state = 0;
}

/**
 * @brief Implements a two-counter debounce state machine.
 * 
 * This logic is robust against noise. It requires DEBOUNCE_TICKS consecutive
 * readings of the *same* state before it confirms a state change.
 * 
 * - count1: Tracks consecutive 'released' (0) readings.
 * - count2: Tracks consecutive 'pressed' (1) readings.
 * 
 * When the button is bouncing, neither counter will reach the DEBOUNCE_TICKS threshold,
 * effectively filtering out the noise.
 */
uint8_t button_update(button_t *btn)
{
    // These counters are 'static' so they retain their value across function calls.
    static uint8_t count1 = 0; // Counter for stable 'released' state
    static uint8_t count2 = 0; // Counter for stable 'pressed' state

    // Read the physical state of the button pin from the input register.
    // The result is either 1 (pressed) or 0 (released).
    uint8_t current_state = (*btn->input_reg & btn->pin_mask) ? 1 : 0;

    // ----- STATE MACHINE LOGIC -----

    if (current_state == 0) {
        // The button is currently reading 'released' (0).

        // Increment the 'released' counter and reset the 'pressed' counter.
        count1++;
        count2 = 0;

        // Check if we have enough consecutive 'released' readings.
        if (count1 >= DEBOUNCE_TICKS) {
            // A stable 'released' state is confirmed.
            
            // Did the state just change from pressed to released?
            if (btn->prev_stable_state == 1) {
                // This is a falling edge event.
                btn->prev_stable_state = 0; // Update the stable state
                led_set(btn, 0);            // Update the LED
            }
            // To prevent multiple events for a single press, we can reset the counter here,
            // or cap it at DEBOUNCE_TICKS. Resetting is simpler.
            count1 = 0;
        }
    } else {
        // The button is currently reading 'pressed' (1).

        // Increment the 'pressed' counter and reset the 'released' counter.
        count2++;
        count1 = 0;

        // Check if we have enough consecutive 'pressed' readings.
        if (count2 >= DEBOUNCE_TICKS) {
            // A stable 'pressed' state is confirmed.

            // Did the state just change from released to pressed?
            if (btn->prev_stable_state == 0) {
                // This is a rising edge event.
                btn->prev_stable_state = 1; // Update the stable state
                led_set(btn, 1);            // Update the LED
                count2 = 0;                 // Reset counter to prevent multiple events
                return 1;                   // Signal that a button press occurred.
            }
        }
    }

    // If no stable edge event was detected in this call, return 0.
    return 0;
}