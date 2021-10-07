#include <stdio.h>
#include "brick.h"
#include "init.h"

#define MOTOR_RIGHT     OUTA
#define MOTOR_LEFT      OUTB
#define MOTOR_BOTH      (MOTOR_LEFT | MOTOR_RIGHT)
#define MOTOR_DROP      OUTC
#define SENSOR_US       IN3

//int max_driving_speed;  // Max speed of driving motors
//int drop_speed;         // Max speed of drop motor

int init(int* max_driving_speed, int* drop_speed){
    printf("Initializing...\n");

    /* Unsuccessful initialization for an unknown reason
     * Print the error and return 0 */
    if(!brick_init()){
        printf("ERROR: Unable to initialize brick. Error called from function init() located in init.c.\n");
        sleep_ms(100);
        return 0;
    }

    /* Check if every necessary component is plugged in
     * If one is not, print an error and return 0
     */
    if(!(tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_) && tacho_is_plugged(MOTOR_DROP, TACHO_TYPE__NONE_) && sensor_is_plugged(SENSOR_US, TACHO_TYPE__NONE_))){
        brick_uninit();
        printf("ERROR: One or more components are not connected. Error called from function init() located in init.c.\n");
        sleep_ms(100);
        return 0;
    }
    
    // Set maximum speed of driving and drop motors if the are given arguments
    if(max_driving_speed)
        *max_driving_speed = tacho_get_max_speed(MOTOR_LEFT, 0);
    if(drop_speed)
        *drop_speed = tacho_get_max_speed(MOTOR_DROP, 0);

    // Reset driving and drop motors
    tacho_reset(MOTOR_BOTH);
    tacho_reset(MOTOR_DROP);

    // Print that initialization was successful and return 1
    printf("Initialization successful!\n"
            "******** Welcome! ********\n");
    sleep_ms(100);
    return 1;
}