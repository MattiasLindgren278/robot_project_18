#include <stdio.h>
#include <unistd.h>
#include "brick.h"
#include "rotation.h"

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define SENSOR_TOUCH	IN1

#define MOTOR_BOTH     	(MOTOR_LEFT | MOTOR_RIGHT)

int max_speed;

int init();

int main(void)
{  
    if(!init()){
        printf("Initialization failed. Shutting down...");
        sleep_ms(1000);
        brick_uninit();
        return 1;
    }


    rotate('r', 90, 0.1);
    sleep_ms(3000);


	brick_uninit();
	printf("Shutting down...\n");
    sleep_ms(1000);
    return 0;
}

int init(){
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
    }
}