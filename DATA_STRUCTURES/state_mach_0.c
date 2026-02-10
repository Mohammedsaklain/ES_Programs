#include <stdio.h>
#include <stdint.h>

typedef enum {
    IDLE = 0,
    RUNNING,
    ERROR
} Mach_States;

enum {
    EVENT_START = 0,
    EVENT_STOP,
    EVENT_FAILURE,
    EVENT_RESET
} event;

Mach_States handle_idle_state(uint8_t event);
Mach_States handle_running_state(uint8_t event);
Mach_States handle_error_state(uint8_t event);

Mach_States (*handler_func[])(uint8_t) = 
{
    [IDLE]    = handle_running_state,
    [RUNNING] = handle_idle_state,
    [ERROR]   = handle_error_state
};

int main(void){
    Mach_States current_state = IDLE;
    printf("Starting in IDLE state\n\n");
    
    uint8_t event;
    uint8_t event_sequence[] = {EVENT_START, EVENT_START, EVENT_FAILURE, EVENT_RESET, EVENT_STOP};

    int i=0;
    while(i<5){
        event = event_sequence[i];
        printf("Current State = %u, Processing Event = %u\n", current_state, event);
        current_state = handler_func[current_state](event);
        i++;
    }
    printf("Finished\n");
    return 0;
}

Mach_States handle_idle_state(uint8_t event){
    printf("Handle Idle State\n");
    if(event==EVENT_START){
        printf("Transition to Running\n");
        return RUNNING;
    } 
    printf("No state change\n");
    return IDLE;
    
}
Mach_States handle_running_state(uint8_t event){
    printf("Handle Running State\n");
    if(event==EVENT_STOP){
        printf("Transition to Idle\n");
        return IDLE;
    } else if(event==EVENT_FAILURE){
        printf("Transition to Error\n");
        return ERROR;
    }
    printf("No state Change\n");
    return RUNNING;
}
Mach_States handle_error_state(uint8_t event){
    printf("Handle Error State\n");
    if(event==EVENT_RESET){
        printf("Transition to Idle\n");
        return IDLE;
    }
    printf("No state change\n");
    return ERROR;
}