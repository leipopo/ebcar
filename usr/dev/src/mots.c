#include "main.h"

void mot_init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

void pwm_dutycycle_calc(pwm_speed_mot *sm)
{
    sm->tar.power_percent = flimf(sm->para.max_power_percent,
                                  -sm->para.max_power_percent,
                                  sm->tar.power_percent);

    sm->cur.power_percent = flimf(sm->tar.power_percent_acc_p * ms2s(mottaskperiod),
                                  -sm->tar.power_percent_acc_n * ms2s(mottaskperiod),
                                  (sm->tar.power_percent - sm->cur.power_percent) * ms2s(mottaskperiod)) +
                            sm->cur.power_percent;

    sm->cur.pwm_dutycycle = fabsf((sm->para.pwm_period - sm->para.pwm_dead_dutycycle) * sm->cur.power_percent) + sm->para.pwm_dead_dutycycle;
}

void pwm_speedmot_calc(pwm_speed_mot *sm)
{
    pwm_dutycycle_calc(sm);

    if (sm->cur.power_percent >= 0)
        sm->cur.dir = 1;
    else if (sm->cur.power_percent < 0)
        sm->cur.dir = -1;
}
