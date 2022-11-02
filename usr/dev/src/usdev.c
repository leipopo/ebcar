#include "main.h"
#include "tim.h"

float dis_fm[samp_num + 1] = {
    NULL,
};
float dis;
int8_t Channel1Edge = 0;
int32_t Channel1HighTime, Channel1RisingTime, Channel1FallingTime;

void usdev_init(void)
{
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    /*防止未使用参数(s)编译警告*/
    // UNUSED(htim);

    if (htim->Instance == htim3.Instance) {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
            if (Channel1Edge == 0) // 捕获上升沿
            {
                Channel1RisingTime = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);                  // 获取上升沿时间点
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING); // 切换捕获极性
                HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);                                             // 切换捕获极性后需重新启动

                Channel1Edge = 1;         // 上升沿、下降沿捕获标志位
            } else if (Channel1Edge == 1) // 捕获下降沿
            {
                Channel1FallingTime = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);                // 获取下降沿时间点
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING); // 切换捕获极性
                HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);                                            // 切换捕获极性后需重新启动

                Channel1HighTime = Channel1FallingTime < Channel1RisingTime ? Channel1FallingTime + 0xffff - Channel1RisingTime + 1 : Channel1FallingTime - Channel1RisingTime;

                // 高电平持续时间 = 下降沿时间点 - 上升沿时间点
                float temp = 0;
                for (int8_t i = 0; i < samp_num; i++) {
                    dis_fm[i] = dis_fm[i + 1];
                    if (dis_fm[i] > temp) {
                        temp = dis_fm[i];
                    }
                }

                dis = temp * 0.1 + dis * 0.9;

                dis_fm[samp_num] = Channel1HighTime * 17.f / 100.f;
                if (dis_fm[samp_num] > 4500.f) {
                    dis_fm[samp_num] = dis;
                }

                if ((fabsf(dis_fm[samp_num] - dis) > 20.f) && (fabsf(dis_fm[samp_num] - dis) < 1000.f)) {
                    dis_fm[samp_num] = dis_fm[samp_num] * 0.6 + dis * 0.4;
                } else if (fabsf(dis_fm[samp_num] - dis) > 1000.f) {
                    dis_fm[samp_num] = dis_fm[samp_num] * 0.2 + dis * 0.8;
                }

                // i++;//累加计数
                Channel1Edge = 0; // 一次采集完毕，清零
            }
        }
    }
}
