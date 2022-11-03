#ifndef MOTS_H
#define MOTS_H

#include "stdint.h"
#include "tim.h"

typedef struct
{
    struct {
        int16_t pwm_period;         // us
        int16_t pwm_dead_dutycycle; // us
        float max_power_percent;    // -1.f--------------------------1.f
    } para;

    struct {
        float power_percent_acc_p; //  /(s*s)
        float power_percent_acc_n; //  /(s*s)
        float power_percent;       // -1.f--------------------------1.f
    } tar;

    struct {
        int16_t pwm_dutycycle;
        int8_t dir;
        float power_percent;
    } cur;

} pwm_speed_mot;

void mot_init(void);

#endif
