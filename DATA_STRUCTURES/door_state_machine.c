#include <stdio.h>
#include <stdint.h>

typedef enum 
{
    STATE_OPEN,
    STATE_CLOSED
} enm_door_state;

typedef struct DoorState
{
    enm_door_state current_state;
    void (*state_handler)(struct DoorState *);
} DoorState;

void handle_open_state(DoorState *ptr);
void handle_closed_state(DoorState *ptr);
void change_state(DoorState *ptr, enm_door_state new_state);

int main(void)
{
    DoorState door = {STATE_CLOSED, handle_closed_state};

    door.state_handler(&door);

    change_state(&door, STATE_OPEN);

    door.state_handler(&door);

    return 0;
}

void handle_open_state(DoorState *ptr)
{
    printf("Door is currently open.\n");
}

void handle_closed_state(DoorState *ptr)
{
    printf("Door is currently closed.\n");
}

void change_state(DoorState *ptr, enm_door_state new_state)
{
    ptr->current_state = new_state;

    switch (new_state)
    {
        case STATE_OPEN:
            ptr->state_handler = handle_open_state;
            break;
        case STATE_CLOSED:
            ptr->state_handler = handle_closed_state;
            break;
    }
}