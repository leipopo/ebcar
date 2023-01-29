#ifndef USDEV_H
#define USDEV_H
#include "stdint.h"
#include "tim.h"
#define samp_num 10
extern float dis_fm[samp_num+1];
extern float dis;
void usdev_init(void);

void ustrigger();
void LED_show(float num);
#endif
