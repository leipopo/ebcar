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

#define wheel0_config  \
    {                  \
        {              \
            1000,      \
            600,      \
            1.f,       \
        },             \
            {          \
                500.f, \
                300.f, \
                0.f,   \
            },         \
            {          \
                0,     \
                1,     \
                0,     \
            },         \
    }

#define wheel1_config  \
    {                  \
        {              \
            1000,      \
            500,      \
            1.f,       \
        },             \
            {          \
                500.f, \
                300.f, \
                0.f,   \
            },         \
            {          \
                0,     \
                1,     \
                0,     \
            },         \
    }

void mot_init(void);
void pwm_speedmot_calc(pwm_speed_mot *sm);

#endif
