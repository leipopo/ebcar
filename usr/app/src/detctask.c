#include "main.h "
#include "bsp_delay.h"

void ustrigger()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    delay_us(20);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void LED_show(float num)
{
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, (uint32_t)(ledmax_pwm-fminf(fmaxf(num - ledmax_pwm*3,0), ledmax_pwm)));
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, (uint32_t)(ledmax_pwm-fminf(fmaxf(num - ledmax_pwm*2,0), ledmax_pwm)));
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, (uint32_t)(ledmax_pwm-fminf(fmaxf(num - ledmax_pwm*1,0), ledmax_pwm)));
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, (uint32_t)(ledmax_pwm-fminf(fmaxf(num - ledmax_pwm*0,0), ledmax_pwm)));
}

void detctask()
{
    for (;;) {
        LED_show(4 * ledmax_pwm * dis / ledshow_dis);
        ustrigger();
        osDelay(detctaskperiod);
    }
}
