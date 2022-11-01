#include "main.h"

void mot_init()
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}


