/* If the sensor value >= 128, then the sensor value is valid(sensor ready) otherwise invalid(sensor not ready)
after 1000 attempts , the timout occurs */


#include <stdio.h>
#include <stdint.h>

#define TARGET_PC 1/* defining TRUE for a safe operation for PC's*/

#if MICROCONTROLLER
/* In Standard computers, this below line will not work & the code will crash as soon it executes,
because the below line declares a memory mapped register (0x08000000) which is not hardcoded in PC's,
So we are using the safe way for the PC's in next declaratins */
#define REG_BASE_ADDR (0x08000000)  /*the address value taken example from STM ARM*/
#define SENSOR_VALUE  (*(volatile uint32_t *)REG_BASE_ADDR)
/* In this line, first (uint32_t *) Typecasts the address(REG_BASE_ADDR) to a pointer 
that points to an unsigned 32-bit integer. The Pointer (uint32_t *) Tells the compiler:
"The memory at this address should be treated as a 32-bit register."*/
#elif TARGET_PC
int volatile sensor_value = 0;
#define SENSOR_VALUE sensor_value
#endif

int poll_sensor(void);
int main(void){ 
    SENSOR_VALUE = 30; /* simulating sensor invalid(sensor not ready) data*/
    int retval = poll_sensor();
    if(retval >= 0){
        printf("Sensor ready: Sensor Value = %d\n",retval);
    } else {
        printf("Timeout: No data is ready\n");
    }


    SENSOR_VALUE = 180; /* Now simulating a valid(sensor ready) data*/
    retval = poll_sensor();
    if(retval >= 0){
        printf("Sensor ready: Sensor Value = %d\n",retval);
    } else {
        printf("Timeout: No data is ready\n");
    }

    return 0;   /* In Embedded C, this should never be executed or Program counter should not enter here*/
}

int poll_sensor(void){
    uint16_t attempts = 0;
    while(attempts < 1000){
        if(SENSOR_VALUE>=128){
            return (int)SENSOR_VALUE;   /* Data is valid, return data */
        }
        attempts++;
    }
    return -1;  /* Time out after 1000 polling attempts */
}