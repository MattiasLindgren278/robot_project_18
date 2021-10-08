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

int max_hastighet;                                  /* Variabel för max hastighet på motorn */
POOL_T usSensor;


void drive(float distance_mm, float speed){

    usSensor = sensor_search(LEGO_EV3_US);          // finns även fler som börjar på US... in och cm. 
    
    us_set_mode_us_dist_cm(usSensor);               // mm och inte cm
    
    float   distance =      distance_mm;            //mm
    float   drive_to_pos = PULS_PER_CM * distance;  //Antalet puls roboten ska köra

    drive_to_pos = (int)drive_to_pos;               //Byter datatyp från int till float

tacho_set_speed_sp(MOTOR_BOTH, max_hastighet * speed); // Helst 0.5
tacho_set_position(MOTOR_BOTH, 0);                  //sätter start position till 0
tacho_set_position_sp(MOTOR_BOTH, drive_to_pos);    // sätter antalet pulsar den ska köra 
tacho_run_to_abs_pos(MOTOR_BOTH);                   // kör motorerna position + position_sp 
}