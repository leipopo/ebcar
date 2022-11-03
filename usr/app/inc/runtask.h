#ifndef RUNTASK_H
#define RUNTASK_H

#include "stdint.h"
#include "mots.h"
#define rotleft 0 
#define rotright 1 
typedef struct
{
    float leftpower;
    float rightpower;
    float maxpower;
    uint8_t rotdir;
}run_date;

extern run_date rundate;
extern pwm_speed_mot wheel[2];

#endif 
