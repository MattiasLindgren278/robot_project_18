#include <stdio.h>
#include "brick.h"
#include <unistd.h>

#define Sleep( msec ) usleep(( msec ) * 1000 ) /* Definerar sleep, Sleep(1000)= 1 sekund */

#define MOTOR_RIGHT    	OUTA
#define MOTOR_LEFT    	OUTB
#define MOTOR_C    		OUTC
#define MOTOR_D    		OUTD
#define SENSOR_TOUCH	IN1
#define SENSOR_2		IN2
#define SENSOR_3		IN3
#define SENSOR_4		IN4

#define MOTOR_BOTH     	( MOTOR_LEFT | MOTOR_RIGHT ) /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

int max_hastighet;         /* variabel för max hastighet på motorn */
POOL_T touchSensor;

int init();
void rotate_right(float, int);
void rotate_left(float, int);

int main( void )
{  
    init();
    rotate_left(0.2, 5000);
    rotate_right(0.2, 5000);
    brick_uninit();
    printf("dying...\n");
    return (0);
}

int init(){

    if (!brick_init()) return (1); /* Initialiserar EV3-klossen */
	printf("*** ( EV3 ) Hello! ***\n");
	Sleep(2000);
	
	if (tacho_is_plugged(MOTOR_C, TACHO_TYPE__NONE_)) {  /* TACHO_TYPE__NONE_ = Alla typer av motorer */
        max_hastighet = tacho_get_max_speed(MOTOR_C, 0);	/* Kollar maxhastigheten som motorn kan ha */
        tacho_reset(MOTOR_C);

    } else {
        printf("Anslut vänster motor i port C,\n");
      	brick_uninit();
        return (0);  /* Stänger av sig om motorern ej är inkopplad */
    }
	
}

void rotate_right(float speed, int runtime_msec){
    tacho_set_speed_sp(MOTOR_C, max_hastighet * -speed);
    tacho_run_forever(MOTOR_C);
    Sleep(runtime_msec);
    tacho_stop(MOTOR_C);
}

void rotate_left(float speed, int runtime_msec){
    tacho_set_speed_sp(MOTOR_C, max_hastighet * speed);
    tacho_run_forever(MOTOR_C);
    Sleep(runtime_msec);
    tacho_stop(MOTOR_C);
}
