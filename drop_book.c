#include <stdio.h>
#include "brick.h"
#include "init.h"

#define MOTOR_DROP      OUTC
#define SENSOR_TOUCH    IN2

int drop_speed;
int max_driving_speed;
POOL_T touchSensor;

void drop();

void drop(){
    /* Set drop speed for medium tacho motor
    * Start medium tacho motor 
    * Wait one second
    * Stop medium tacho motor */
    printf("Dropping book\n");
    tacho_set_speed_sp(MOTOR_DROP, drop_speed);
    tacho_run_forever(MOTOR_DROP);
    sleep_ms(1000);
    tacho_stop(MOTOR_DROP);

    /* Set speed to reverse dropping mechanism for medium tacho motor
    * Start the medium tacho motor 
    * Wait one second
    * Stop the medium tacho motor */
    printf("Resetting position\n");
    tacho_set_speed_sp(MOTOR_DROP, drop_speed * -1);
    tacho_run_forever(MOTOR_DROP);
    sleep_ms(1000);
    tacho_stop(MOTOR_DROP);
}

int main(void){  
    
    //Init failed, "dirty" exit
    if (!init(&max_driving_speed,&drop_speed)){
        printf("Shutting down due to an error...\n");
        sleep_ms(3000);
        return 1;
    }

    touchSensor = sensor_search(LEGO_EV3_TOUCH);
	touch_set_mode_touch(touchSensor);

    printf("Press sensor to begin routine.\n");
    sleep_ms(100);
    while(!sensor_get_value(0, touchSensor, 0));

    //The routine
    drop();

    printf("Routine done. Press sensor to exit...\n");
    sleep_ms(100);

    //Shutdown robot by pressing the touch sensor
	while(!sensor_get_value(0, touchSensor, 0));
	brick_uninit();
	printf("Shutting down...\n");
    sleep_ms(1500);
    return 0;
}