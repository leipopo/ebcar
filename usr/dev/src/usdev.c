#include "main.h"

uint8_t dis_fm = 0;
uint8_t Channel1Edge = 0;
uint16_t Channel1HighTime, Channel1RisingTime, Channel1FallingTime;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    /*防止未使用参数(s)编译警告*/
    UNUSED(htim);

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
                dis_fm = Channel1HighTime * 17 / 100; // 计算超声波测量距离

                // i++;//累加计数
                Channel1Edge = 0; // 一次采集完毕，清零
            }
        }
    }
}