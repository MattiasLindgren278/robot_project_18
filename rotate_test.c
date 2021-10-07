#include <stdio.h>
#include "brick.h"
#include <unistd.h>

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define SENSOR_TOUCH	IN1

#define MOTOR_BOTH     	(MOTOR_LEFT | MOTOR_RIGHT)

int max_speed;
POOL_T touch_sensor;

int init();
void rotate(char, int);

int main( void )
{  
    if(!init()){
        printf("Initialization failed. Shutting down...");
        sleep_ms(1500);
        brick_uninit();
        return 1;
    }

    touch_sensor = sensor_search(LEGO_EV3_TOUCH);
	touch_set_mode_touch(touch_sensor);

    rotate('r', 90);
    rotate('l', 90);

    printf("Press sensor to exit.\n");
    sleep_ms(100);

    //Shutdown robot by pressing the touch sensor
	while(!sensor_get_value(0, touch_sensor, 0));
	brick_uninit();
	printf("Shutting down...\n");
    sleep_ms(1500);
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
        max_speed = tacho_get_max_speed(MOTOR_BOTH, 0);
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

void rotate(char direction, int degrees){
    switch(direction){
        case('r'):
            printf("Rotating right %d degrees\n", degrees);
            tacho_set_speed_sp(MOTOR_LEFT, max_speed * 0.25f);
            tacho_set_speed_sp(MOTOR_RIGHT, max_speed * -0.25f);
            tacho_set_position_sp(MOTOR_LEFT, degrees);
            tacho_set_position_sp(MOTOR_RIGHT, -degrees);
            tacho_run_to_rel_pos(MOTOR_BOTH);
            break;
        case('l'):
            printf("Rotating left %d degrees\n", degrees);
            tacho_set_speed_sp(MOTOR_RIGHT, max_speed * 0.25f);
            tacho_set_speed_sp(MOTOR_LEFT, max_speed * -0.25f);
            tacho_set_position_sp(MOTOR_RIGHT, degrees);
            tacho_set_position_sp(MOTOR_LEFT, -degrees);
            tacho_run_to_rel_pos(MOTOR_BOTH);
            break;
        default:
            printf("Parameter direction only accepts argument 'r' or 'l' in function rotate().\n");
            break;
    }
}
