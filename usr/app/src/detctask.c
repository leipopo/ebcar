#include "main.h "
#include "bsp_delay.h"

void ustrigger()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
    delay_us(20);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
}

void detctask()
{
    for(;;)
    {
        ustrigger();
        osDelay(fetctaskperiod);
    }
}
