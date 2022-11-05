#include "main.h "

run_date rundate;
pwm_speed_mot wheel[2] = {wheel0_config, wheel1_config};

void maxpower_set(run_date *rd)
{
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_RESET) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_RESET) {
            rd->maxpower = 1;
        } else {
            rd->maxpower = 0.3f;
        }
    } else {
        rd->maxpower = 0;
    }
}

void lrpower_calc(run_date *rd)
{
    if (rd->rotdir == rotleft) {
        rd->leftpower = rd->maxpower * ((fmaxf(fminf(dis, ledshow_dis) - dangerdis, 0) - (ledshow_dis - dangerdis) / 2.f) / ((ledshow_dis - dangerdis) / 2.f));
        rd->rightpower = rd->maxpower;
    } else if (rd->rotdir == rotright) {
        rd->rightpower = rd->maxpower * ((fmaxf(fminf(dis, ledshow_dis) - dangerdis, 0) - (ledshow_dis - dangerdis) / 2.f) / ((ledshow_dis - dangerdis) / 2.f));
        rd->leftpower = rd->maxpower;
    }
}

void rundate2whedate(pwm_speed_mot wd[2], run_date *rd)
{
    wd[0].tar.power_percent = rd->leftpower;
    wd[1].tar.power_percent = rd->rightpower;
    pwm_speedmot_calc(&wd[0]);
    pwm_speedmot_calc(&wd[1]);
}

void rundate_update(pwm_speed_mot wd[2], run_date *d)
{
    maxpower_set(d);
    lrpower_calc(d);
    rundate2whedate(wd, d);
}

void set_dir()
{
    if (wheel[0].cur.dir == 1) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
    } else if (wheel[0].cur.dir == -1) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
    }else if (wheel[0].cur.dir == 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
    }

    if (wheel[1].cur.dir == 1) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    } else if (wheel[1].cur.dir == -1) {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    }else if (wheel[1].cur.dir == 0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    }

}

void set_pwm()
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, wheel[0].cur.pwm_dutycycle);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, wheel[1].cur.pwm_dutycycle);
}

void wheel_ctrl()
{
    set_dir();
    set_pwm();
}

void runtask()
{
    
    for (;;) {
        rundate_update(wheel, &rundate);
        wheel_ctrl();
        osDelay(mottaskperiod);
    }
}
