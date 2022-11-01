#ifndef MOTS_H
#define MOTS_H

#include "tim.h"

typedef struct
{
    int16_t pwm_dutycycle;
    int16_t pwm_period;
    int16_t pwm_dead_dutycycle;

    float acc;
    float power_percent;
}mot;

void mot_init();


#endif 