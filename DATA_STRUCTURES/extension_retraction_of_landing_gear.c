/* File: extension_retraction_of_landing_gear.c */
/* Aircraft Landing Gear State Machine - Safety Critical System */
/*                  STATE TRANSITION DIAGRAM:
 * 
 *                     [GROUND, LEVER=DOWN]
 *                            |
 *                            v
 *                    +---------------+
 *                    |   GEAR_DOWN   |<-----------------+
 *                    | Lights: GREEN |                  |
 *                    | Pump: OFF     |                  |
 *                    +---------------+                  |
 *                            |                          |
 *                  (Lever UP + In AIR)                  |
 *                            |                          |
 *                            v                          |
 *                  +------------------+                 |
 *                  | WAITING_TAKEOFF  |                 |
 *                  | Lights: GREEN    |                 |
 *                  | 2sec timer       |                 |
 *                  +------------------+                 |
 *                     |            |                    |
 *          (2s elapsed)  (Touch ground OR Lever DOWN)   |
 *                     |            +--------------------+
 *                     v
 *                +-------------+
 *                | RISING_GEAR |<----------+
 *                | Lights: RED |           |
 *                | Pump: UP    |           |
 *                +-------------+           |
 *                     |        |           |
 *          (Gears UP) |        |(Lever DOWN)
 *                     |        |           |
 *                     v        v           |
 *                +---------+  +---------------+
 *                | GEAR_UP |  | LOWERING_GEAR |
 *                | Lights: |  | Lights: RED   |
 *                |   OFF   |  | Pump: DOWN    |
 *                +---------+  +---------------+
 *                     |              |
 *              (Lever DOWN)   (Gears DOWN)
 *                     |              |
 *                     +------+-------+
 *                            |
 *                            v
 *                    [Back to GEAR_DOWN]
 */

#include <stdio.h>
#include <stdint.h>

#define LEVER_UP        1   /* Pilot lever positions */
#define LEVER_DOWN      0
#define SQUAT_AIR       0   /* Squat switch positions */
#define SQUAT_GROUND    1  
#define PUMP_OFF        0   /* Hydraulic pump */
#define PUMP_ON         1
#define PUMP_DIR_DOWN   1   /* Pump direction */
#define PUMP_DIR_UP     0

#define TAKEOFF_DELAY_MS        2000    /* 2 second delay before retraction */
#define GEAR_MOVEMENT_TIME_MS   5000    /* 5 seconds to fully extend/retract */
#define GEAR_TIMEOUT_MS         10000   /* 10 second timeout for stuck gears */
#define SYSTEM_TICK_MS          10      /* 10ms system tick for simulation */

typedef enum {
    GEAR_DOWN_S,
    WAITING_FOR_TAKEOFF_S,
    RISING_GEAR_S,
    LOWERING_GEAR_S,
    GEAR_UP_S,
    FAULT_S     /* fault state */
} Type_system_states;

typedef enum {
    OFF_LIGHTS,     /* all the lights are off while in AIR */
    RED_LIGHTS,     /* red lights while in transit process */
    GREEN_LIGHTS    /* green lights when gears are fully deployed */
} Type_gear_light;

/* All Gear position(hydraulic gear position) */
/* nose, right & left leg gears */
typedef enum {
    UP_POS_GEAR,
    DOWN_POS_GEAR,
    TRANSIT_POS_GEAR    /* gear transition */
} Type_gears;

typedef enum {
    NO_FAULT,
    TIMEOUT_FAULT,
    SENSOR_FAULT
} Type_fault;

/* INPUTS: would come from hardware in real world */
uint8_t pilot_lever          = LEVER_DOWN;      /* variable for pilot lever action, 0 = falling, 1= rising */
uint8_t squat_switch         = SQUAT_GROUND;    /* switch at nose gear which shows plane in AIR(0) or GROUND(1) */

/* OUTPUS: come from real hardware world */
uint8_t pump_status          = PUMP_OFF;        /* to show the status of pumps(to all the gears) */
uint8_t pump_direction       = PUMP_DIR_DOWN;   /* related to pumping direction, wether to pressurising(DOWN) or depressurize(UP) the hydraulics */

Type_system_states  system_state        = GEAR_DOWN_S;       /* system states */
Type_gear_light     current_lights_clr  = GREEN_LIGHTS;      /* to represent the current lights status: Off, Red, Green */
Type_gears          gears_position      = DOWN_POS_GEAR;     /* to show gears UP/DOWN movements */
Type_fault          fault_code          = NO_FAULT;

/* State machine variables */
volatile uint32_t system_tick_counter   = 0;      /* System tick counter (incremented by timer ISR) */
uint8_t timer_flag                      = 0;      /* flag to trigger the timer */
uint8_t previous_lever_state            = LEVER_DOWN;
uint32_t state_timer                    = 0;
uint32_t movement_start_time            = 0;
uint8_t  state_entry_flag               = 1;     /* Flag to detect state entry */
/* NOTE: If the pump itself is turned off, then the direction of pump pressurization doesn't matters */

void Default_Gear_State(void);
void gear_down(void);
void waiting_for_takeoff(void);
void rising_gear(void);
void lowering_gear(void);
void gear_up(void);
uint8_t Timer_Callback(uint32_t time);   /* returns 1 when timer time period expired or reached */

/* creating pointer function to call different states */
void (*handler_state[])() = {
    gear_down,
    waiting_for_takeoff,
    rising_gear,
    lowering_gear,
    gear_up
};

int main(void){
    Default_Gear_State();
    while(1){
        handler_state[system_state]();  /* repeatedly call the state handler to process the system states */
        current_tick++;
    }
    return 0;
}

void Default_Gear_State(void){
    system_state        = GEAR_DOWN_S;    /* default is gear down */
    current_lights_clr  = GREEN_LIGHTS; /* during stationary mode, gears are fully down, so green */
    timer_flag = 0;                     /* reset the timer  */
}

void gear_down(void){
    if((pilot_lever==LEVER_UP) && (previous_lever_state==LEVER_DOWN) && (squat_switch==SQUAT_AIR)){
        timer_flag = 1;
        system_state = WAITING_FOR_TAKEOFF_S; /* system state to waiting for takeoff*/
    }
    previous_lever_state = pilot_lever;     /* for edge detection */
}

void waiting_for_takeoff(void){

    if (timer_flag) {               /* If the timer is enabled */
        timer_flag = 0;
        Timer_Callback(2000);       /* timer callback function to simulate 2 seconds */
        if()
        system_state = RISING_GEAR_S; /* if 2s is over while we are in AIR, switch to rising gear state */
    }

    /* if we are in ground or pilot wishes to land */
    if((squat_switch==SQUAT_GROUND) || (pilot_lever==LEVER_DOWN)){
        timer_flag = 0;  /* reset timer */
        system_state = GEAR_DOWN_S;
        previous_lever_state = pilot_lever;
    }
}

void rising_gear(void){
    /* once all the gears are up, lets move to gear up state */
    if(gears_position==UP_POS_GEAR){
        pump_status = PUMP_OFF;
        current_lights_clr = OFF_LIGHTS;
        system_state = GEAR_UP_S;
    }

    /* If the pilot wishes to down the gears */
    if(pilot_lever==LEVER_DOWN){
        pump_status     = PUMP_ON;          /* First turn on the pump */
        pump_direction  = PUMP_DIR_DOWN;    /* pressurize */
        system_state    = LOWERING_GEAR_S;    /* update the system state */
        previous_lever_state = pilot_lever;
    }   
}

void lowering_gear(void){
    /* once all the gears down, move to gear down state */
    if(gears_position==DOWN_POS_GEAR){
        pump_status     = PUMP_ON;
        pump_direction  = PUMP_DIR_DOWN;
        system_state    = GEAR_DOWN_S;
    }

    if(pilot_lever==LEVER_UP){
        pump_status          = PUMP_ON;
        pump_direction       = PUMP_DIR_UP;
        previous_lever_state = pilot_lever;
        system_state         = RISING_GEAR_S;
    }
}

void gear_up(void){
    if(pilot_lever==LEVER_DOWN){
        pump_status     = PUMP_ON;
        pump_direction  = PUMP_DIR_DOWN;
        system_state    = LOWERING_GEAR_S; 
    }
}

uint8_t Timer_Callback(uint32_t time){
    uint32_t timer_cnt = 0;    /* timer variable to mimic the actual hardware timer */
    while(time!=timer_cnt){
        timer_cnt++;    /* simply just increment the global variable to mimic the timer behaviour */
    }
    return 1;
}