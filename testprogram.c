#include <stdio.h>
#include "brick.h"
#include "init.h"
#include "from_wall.h"
#include "drive.h"

#define sleep( msec ) usleep(( msec ) * 1000 ) /* Definerar sleep, Sleep(1000)= 1 sekund */

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_C    	OUTC
#define MOTOR_D    	OUTD
#define SENSOR_TOUCH	IN1
#define SENSOR_2	IN2
#define SENSOR_3	IN3
#define SENSOR_4	IN4

#define MOTOR_BOTH     	( MOTOR_LEFT | MOTOR_RIGHT ) /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

POOL_T usSensor;
int max_driving_speed;  // Max speed for driving motors

int main(void){
    if(!init(&max_driving_speed, 0)){
        return 1;
}
    drive(2500, 0.5);
    from_wall(300, 0.5);
    return 0;
}
