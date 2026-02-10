#ifndef _DEBOUNCE_H_
#define _DEBOUNCE_H_

#include <stdint.h>

/**
 * @brief The number of consecutive identical readings required to confirm a stable button state.
 * 
 * This value determines the sensitivity of the debounce filter. A higher value provides
 * more robust debouncing against noisy buttons but introduces a longer delay in detection.
 * A lower value results in quicker detection but may be susceptible to noise.
 */
#define DEBOUNCE_TICKS 5

/**
 * @brief Structure to hold all the necessary information for managing a single button.
 *
 * This struct encapsulates the hardware registers, pin configuration, and state machine
 * variables required to debounce and read a button's state.
 */
typedef struct  
{
    /**
     * @brief Pointer to the hardware input register (e.g., PINx on AVR).
     * 
     * 'const volatile' means:
     * - 'const': The program code cannot change the value pointed to by 'input_reg'.
     * - 'volatile': The value can be changed at any time by external factors (e.g., hardware),
     *   so the compiler should not optimize away reads from this address.
     */
    const volatile  uint32_t * input_reg;

    /**
     * @brief Pointer to the hardware output register (e.g., PORTx on AVR).
     * 
     * 'volatile' ensures that any write to this address is not optimized away by the compiler,
     * as it can affect external hardware (like an LED).
     */
    volatile        uint32_t * output_reg;

    /**
     * @brief A bitmask used to isolate the specific bit for this button within the input register.
     * For example, for pin 3, the mask would be (1 << 3), which is 0x08.
     */
    uint8_t pin_mask;

    /**
     * @brief Stores the last confirmed stable state of the button (0 for released, 1 for pressed).
     *
     * This is a 1-bit bit-field, which is a memory optimization to use only a single bit
     * for this boolean-like flag. It's used by the state machine to detect a *change*
     * in stable state (i.e., a rising or falling edge).
     */
    uint8_t prev_stable_state : 1;
} button_t;


/**
 * @brief Initializes a button_t structure.
 *
 * @param btn Pointer to the button_t struct to be initialized.
 * @param input Pointer to the hardware input register.
 * @param output Pointer to the hardware output register.
 * @param pin_number The pin number (0-31) of the button.
 */
void button_init(button_t * btn, const volatile uint32_t * input, volatile uint32_t * output, uint8_t pin_number);

/**
 * @brief Sets the state of an LED connected to the button's output register.
 *
 * @param btn Pointer to the button_t struct containing the output register.
 * @param state The desired state (0 for off, 1 for on).
 */
void led_set(button_t *btn, uint8_t state);

/**
 * @brief Updates the button's debounce state machine.
 * 
 * This function should be called periodically at a fixed interval (e.g., every 1ms from a timer interrupt).
 * It reads the button's current state, filters out noise, and identifies stable press/release events.
 *
 * @param btn Pointer to the button_t struct to be updated.
 * @return Returns 1 on a newly detected stable press (rising edge), otherwise returns 0.
 */
uint8_t button_update(button_t * btn);

#endif