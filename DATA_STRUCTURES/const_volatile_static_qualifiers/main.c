#include <stdio.h>
#include <stdint.h>
#include "debounce.h"

/**
 * @brief Main function to run the button debounce simulation.
 */
int main(void){
    
    // ----- 1. Simulation Setup -----
    // In a real embedded system, these registers would be hardware features (e.g., PINA, PORTA).
    // Here, we create variables in memory to simulate their behavior.
    // 'static volatile' ensures the compiler treats them like real hardware registers.
    static volatile uint32_t SIM_INPUT  = 0; // Simulates the hardware input register (e.g., PINx)
    static volatile uint32_t SIM_OUTPUT = 0; // Simulates the hardware output register (e.g., PORTx)

    // Declare a local variable for our button's state and configuration.
    button_t btn;
    
    // Initialize the button struct, telling it which registers and pin to use.
    // This is a crucial step to link our abstract button 'btn' to the 'hardware'.
    button_init(&btn, &SIM_INPUT, &SIM_OUTPUT, 3);  // We are using pin 3.

    // ----- 2. Test Data -----
    // This array represents the raw signal from a physical button over 20 time-steps ('ticks').
    // It includes a period of being released, a noisy 'bouncing' period, and a stable 'pressed' period.
    const uint8_t input_sequence[] = {
        0,0,0,0,0,          // 5 ticks: Cleanly released
        1,0,1,0,1,          // 5 ticks: Bouncing noise after initial press
        1,1,1,1,1,1,1,1,1,1 // 10 ticks: Stable press
    };

    printf("System started\r\n");

    // ----- 3. Simulation Loop -----
    // This loop iterates through the 'input_sequence', simulating the passage of time.
    for(uint8_t tick = 0; tick < 20; tick++){
        printf("Tick = %d\n", tick);

        // Set the simulated hardware input based on the current value in our test sequence.
        if(input_sequence[tick]){
            printf(" D = 1 (Raw Signal)\n");
            SIM_INPUT |= btn.pin_mask;
        } else {
            printf(" D = 0 (Raw Signal)\n");
            SIM_INPUT &= ~btn.pin_mask;
        }

        // ----- 4. Debounce Execution -----
        // In a real system, `button_update` would be called by a periodic timer (e.g., every 1ms).
        // To simulate this, we call it multiple times for each 'tick' of our main loop.
        // This gives the debouncer enough samples to distinguish a stable state from noise.
        // If we only called it once per tick, the bouncing signal (1,0,1,0,1) would never
        // allow the debounce counters to build up, and the press would be missed.
        for (int i = 0; i < DEBOUNCE_TICKS; i++) {
            // The button_update function runs its state machine on the current SIM_INPUT value.
            // It will only return 1 on the exact tick that a stable press is *first* detected.
            if(button_update(&btn)){
                printf("Tick %2d: DEBOUNCED BUTTON PRESS detected (Rising Edge)\n", tick);
            }
        }
    }

    // Check the final state of the simulated LED output.
    printf("Final SIM_OUTPUT = 0x%08X (should be 0x00000001)\n", (unsigned)SIM_OUTPUT);
    
    return 0;
}
