#include <stdio.h>
#include "brick.h"
#include "drive.h"

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_C    	OUTC
#define MOTOR_D    	OUTD
#define SENSOR_TOUCH	IN1
#define SENSOR_2	IN2
#define SENSOR_3	IN3
#define SENSOR_4	IN4

#define MOTOR_BOTH  ( MOTOR_LEFT | MOTOR_RIGHT )    /* Bitvis ELLER ger att båda motorerna styrs samtidigt */
#define PULS_PER_CM 2.13427856547123f               /* Antalet pulsar per mm. 350 puls är ett snurr*/

POOL_T usSensor;


void drive(int distance_mm, float speed){

    usSensor = sensor_search(LEGO_EV3_US);          // finns även fler som börjar på US... in och cm. 
    
    us_set_mode_us_dist_cm(usSensor);               // mm och inte cm
    //int   drive_to_pos = PULS_PER_CM * distance_mm;  //Antalet puls roboten ska köra

    //drive_to_pos = (int)drive_to_pos;               //Byter datatyp från int till float

tacho_set_speed_sp(MOTOR_BOTH, tacho_get_max_speed(MOTOR_LEFT, 0) * speed); // Helst 0.5
tacho_set_position(MOTOR_RIGHT, 0);                  //sätter start position till 0
tacho_set_position(MOTOR_LEFT, 0);                  //sätter start position till 0
tacho_set_position_sp(MOTOR_RIGHT, distance_mm * PULS_PER_CM);    // sätter antalet pulsar den ska köra 
tacho_set_position_sp(MOTOR_LEFT, distance_mm * PULS_PER_CM);    // sätter antalet pulsar den ska köra 
tacho_run_to_rel_pos(MOTOR_BOTH);                   // kör motorerna position + position_sp 
}