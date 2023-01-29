#include "main.h "

void detctask()
{
    for (;;) {
        LED_show(4 * ledmax_pwm * dis / ledshow_dis);
        ustrigger();
        osDelay(detctaskperiod);
    }
}
