#include "main.h "

run_date rundate;

void maxpower_set(run_date *rd)
{
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_RESET) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_RESET) {
            rd->maxpower = 1;
        } else {
            rd->maxpower = 0.5;
        }
    } else {
        rd->maxpower = 0;
    }
}

void lrpower_calc(run_date *rd)
{
    if(rd->rotdir==1)
    {
        rd->leftpower*(fmaxf(fminf(dis,ledshow_dis)-dangerdis,0))
    }
}

void rundate_update(run_date *d)
{
    maxpower_set(d);
}
void runtask()
{
    for (;;) {
        rundate_update(&rundate);
        osDelay(mottaskperiod);
    }
}
