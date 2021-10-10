#include <stdio.h>
#include "brick.h"
#include "robot.h"

int main(void){
    if(!init())
        return 1;

    rotate('l', 90, 1);

    drop();

    find_wall();

    drive(600, 0.2f);

    from_wall(300, 0.4f);

    brick_uninit();
    return 0;
}