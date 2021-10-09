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
drop_speed = tacho_get_max_speed(MOTOR_DROP, 0) * 0.1f;
    
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