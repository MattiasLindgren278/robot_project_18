#include <stdio.h>
#include "brick.h"
#include "init.h"

#define MOTOR_DROP      OUTC

int drop_speed;
int max_driving_speed;

void drop_book();

void drop_book(){
    /* Set drop speed for motor drop
    * Start motor drop
    * Wait one second
    * Stop motor drop */
    printf("Dropping book\n");
    tacho_set_speed_sp(MOTOR_DROP, drop_speed);
    tacho_run_forever(MOTOR_DROP);
    sleep_ms(1000);
    tacho_stop(MOTOR_DROP);

    /* Set drop speed * -1 for motor drop 
    * Start motor drop
    * Wait one second
    * Stop drop motor */
    printf("Resetting position\n");
    tacho_set_speed_sp(MOTOR_DROP, drop_speed * -1);
    tacho_run_forever(MOTOR_DROP);
    sleep_ms(1000);
    tacho_stop(MOTOR_DROP);
}