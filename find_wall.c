#include <stdio.h>
#include <unistd.h>
#include "brick.h"
#include "rotation.h"
#include "init.h"

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define SENSOR_3        IN3

#define MOTOR_BOTH     	(MOTOR_LEFT | MOTOR_RIGHT)

int max_driving_speed;
POOL_T sensor_us;

//int init();

int main(void)
{  
    if(!init(&max_driving_speed, 0))
        return 1;

    int min_value = 2500;

    sensor_us = sensor_search(LEGO_EV3_US);
    us_set_mode_us_dist_cm(sensor_us); // mm och inte cm

    rotate('r', 360, 0.05);
    sleep_ms(10);
    while (tacho_get_duty_cycle_sp(MOTOR_RIGHT, 0)){
        int curr_value = sensor_get_value0(sensor_us, 0);

        if (curr_value < min_value)
            min_value = curr_value;

        printf("curr_value: %d", curr_value);
        printf("min_value: %d", min_value);
        sleep_ms(5);
    }


    
    rotate('r', 360, 0.1);
    sleep_ms(10);
    while (tacho_get_duty_cycle_sp(MOTOR_RIGHT, 0)){
        int curr_value = sensor_get_value0(sensor_us, 0);

        printf("curr_value: %d", curr_value);
        printf("min_value: %d", min_value);

        if (curr_value <= min_value){
            tacho_stop(MOTOR_BOTH);
            printf("Stopping");
        }
    }

    sleep_ms(3000);

	brick_uninit();
	printf("Shutting down...\n");
    sleep_ms(1000);
    return 0;
}


/*int init(){
    printf("Initializing...\n");

    if (!brick_init()){
        printf("ERROR: Unable to initialize brick.\n");
        sleep_ms(100);
        return 0;
    }

    if (tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_)){
        max_speed = tacho_get_max_speed(MOTOR_LEFT, 0); 
        tacho_reset(MOTOR_BOTH);
        printf("Initialization successful!\n"
               "******** Welcome! ********\n");
        sleep_ms(100);
        return 1;
    } 
    else{
        brick_uninit();
        printf("ERROR: No motor connected.\n"
        "Connect the right motor to port A and the left motor to port B.\n");
        sleep_ms(100);
        return 0;
}*/