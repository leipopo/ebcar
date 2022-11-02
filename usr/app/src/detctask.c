#include "main.h "

void ustrigger()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,SET);
}

void detctask()
{
    for(;;)
    {
        osDelayUntil(fetctaskperiod);
    }
}