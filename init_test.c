#include <stdio.h>
#include "brick.h"
#include "init.h"

int max_driving_speed;

int main(void){
    if(!init(&max_driving_speed, 0))
        return 1;

    tacho_set_speed_sp(OUTA, max_driving_speed * 1);
    tacho_run_forever(OUTA);
    sleep_ms(1000);
    tacho_stop(OUTA);

    brick_uninit();
    return 0;
}