/* File: power_management_state_machine.c */

#include <stdio.h>
#include <stdint.h>

/* System States */
typedef enum {
    IDLE,
    ACTIVE,
    SLEEP
} state_system;

/* Events in the system */
typedef enum {
    USER_ACTIVITY,
    TIMEOUT,
    WAKEUP
} events_system;

/* System transitions with different events & state
|state  |     event0    | state |  event1 | state | event2 | state  |
ACTIVE  : USER_ACTIVITY → ACTIVE, TIMEOUT → IDLE,  WAKEUP → ACTIVE.
IDLE    : USER_ACTIVITY → ACTIVE, TIMEOUT → SLEEP, WAKEUP → ACTIVE.
SLEEP   : USER_ACTIVITY → ACTIVE, TIMEOUT → SLEEP, WAKEUP → ACTIVE 
*/
int8_t powermgr_init(void);             /* To initialize state machine */
void powermgr_process_event(void);      /* To handle events & update state */
void powermgr_get_state(void);          /* To retrieve the current state */


int main(void){

    return 0;
}

/* Initialize state machine */
int8_t powermgr_init(void){
    
}
