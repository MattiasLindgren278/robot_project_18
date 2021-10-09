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

int main(void)
{  
    if(!init(&max_driving_speed, 0))
        return 1;

    int min_value = 2500;

    sensor_us = sensor_search(LEGO_EV3_US);
    us_set_mode_us_dist_cm(sensor_us); // mm och inte cm

    rotate('r', 360, 0.1);
    while (tacho_is_running(MOTOR_RIGHT)){
        int curr_value = sensor_get_value0(sensor_us, 0);

        if (curr_value < min_value)
            min_value = curr_value;
        //printf("curr_value: %d\n", curr_value);
        //printf("min_value: %d\n", min_value);
    }


    
    rotate('r', 360, 0.1);
    while (tacho_is_running(MOTOR_RIGHT)){
        int curr_value = sensor_get_value0(sensor_us, 0);

        //printf("curr_value: %d\n", curr_value);
        //printf("min_value: %d\n", min_value);

        if (curr_value <= min_value)
            tacho_stop(MOTOR_BOTH);
    }

    sleep_ms(3000);

	brick_uninit();
	printf("Shutting down...\n");
    sleep_ms(1000);
    return 0;
}