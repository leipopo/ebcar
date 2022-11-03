#include "main.h "

run_date rundate;
pwm_speed_mot wheel[2]={default_pwmmot_config,default_pwmmot_config};

void maxpower_set(run_date *rd)
{
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_RESET) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_RESET) {
            rd->maxpower = 0.8;
        } else {
            rd->maxpower = 0.5;
        }
    } else {
        rd->maxpower = 0;
    }
}

void lrpower_calc(run_date *rd)
{
    if(rd->rotdir==rotleft)
    {
        rd->leftpower=rd->maxpower*((fmaxf(fminf(dis,ledshow_dis)-dangerdis,0)-(ledshow_dis-dangerdis)/2.f)/((ledshow_dis-dangerdis)/2.f));
        rd->rightpower=rd->maxpower;
    }
    else if (rd->rotdir==rotright)
    {
        rd->rightpower=rd->maxpower*((fmaxf(fminf(dis,ledshow_dis)-dangerdis,0)-(ledshow_dis-dangerdis)/2.f)/((ledshow_dis-dangerdis)/2.f));
        rd->leftpower=rd->maxpower;
    }
}

void rundate2whedate(pwm_speed_mot wd[2],run_date *rd)
{
    wd[0].tar.power_percent=rd->leftpower;
    wd[1].tar.power_percent=rd->rightpower;
    pwm_speedmot_calc(&wd[0]);
    pwm_speedmot_calc(&wd[1]);
}

void rundate_update(pwm_speed_mot wd[2],run_date *d)
{
    maxpower_set(d);
    lrpower_calc(d);
    rundate2whedate(wd,d);
}
void runtask()
{
    for (;;) {
        rundate_update(wheel,&rundate);
        osDelay(mottaskperiod);
    }
}
