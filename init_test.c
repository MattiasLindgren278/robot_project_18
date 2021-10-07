#include <stdio.h>
#include "brick.h"
#include "init.h"
#include "rotation.h"

int main(void){
    if(!init())
        return 1;

    rotate('l', 45, 0.3f);

    brick_uninit();
    return 0;
}