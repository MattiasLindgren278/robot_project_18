#include <stdio.h>
#include "brick.h"
#include <unistd.h>

#define sleep(msec) usleep((msec) * 1000)

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_C    		OUTC
#define MOTOR_D    		OUTD
#define SENSOR_TOUCH	IN1
#define SENSOR_2		IN2
#define SENSOR_3		IN3
#define SENSOR_4		IN4

#define MOTOR_BOTH     	(MOTOR_LEFT | MOTOR_RIGHT)

int max_hastighet;
POOL_T touchSensor;
POOL_T usSensor;

int init();
void rotate(char, int);

int main(void){

     /*if(!sensor_is_plugged(SENSOR_3, SENSOR_TYPE__NONE_)) {
        printf("Stoppa in sensorn i port 3\n");
        brick_uninit();
        return(0);
    }*/

    init();

    usSensor = sensor_search(LEGO_EV3_US);
    us_set_mode_us_dist_cm(usSensor);
    rotate('R', 90);
    

    brick_uninit();
}

int init(){
    printf("Initializing...\n");

    if (!brick_init()){
        printf("ERROR: Unable to initialize brick.\n");
        sleep(100);
        return 0;
    }

    if (tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )){
        max_hastighet = tacho_get_max_speed(MOTOR_LEFT, 0);
        tacho_reset(MOTOR_BOTH);
        printf("Initialization successful!\n"
               "******** Welcome! ********\n");
        sleep(100);
        return 1;
    } 
    else{
        brick_uninit();
        printf("ERROR: No motors connected.\n"
        "Connect left motor to port A and right motor to port B.\n");
        sleep(100);
        return 0;
    }
}

void rotate(char direction, int degrees){
    tacho_set_position_sp(MOTOR_BOTH,0);
    switch(direction){
        case ('R'):
            printf("Rotating right\n");
            // Set speed for individual motors
            tacho_set_speed_sp(MOTOR_LEFT, max_hastighet * 0.5);
            tacho_set_speed_sp(MOTOR_RIGHT, max_hastighet * -0.5);
            // Start both motors
            
            while (tacho_get_position_sp(MOTOR_RIGHT,0) < degrees)
            {
                printf("%d", tacho_get_position_sp(MOTOR_RIGHT,0));
                tacho_run_to_rel_pos(MOTOR_BOTH);
            }
            break;
        case ('L'):
            printf("Rotating left\n");
            // Set speed for individual motors
            tacho_set_speed_sp(MOTOR_RIGHT, max_hastighet * 0.5);
            tacho_set_speed_sp(MOTOR_LEFT, max_hastighet * -0.5);
            // Start both motors
            while (tacho_get_position_sp(MOTOR_BOTH,0) < degrees)
            {
                tacho_run_forever(MOTOR_BOTH);
            }      
                break;
        default:
            printf("Incorrect direction given in function rotate(). Valid directions: 'R' or 'L'.\n");
            return;
    }
    sleep(100);
    tacho_stop(MOTOR_BOTH);
}

