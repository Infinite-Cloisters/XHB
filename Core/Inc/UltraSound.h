//
// Created by 28035 on 2023/11/11.
//

#ifndef XHB_ULTRASOUND_H
#define XHB_ULTRASOUND_H

#include "main.h"

//根据主频计算100Mhz 周期为10ns


void HAL_Delay_us(uint16_t Delay);

void UltraSound_SendTrig();
void UltraSound_SendTrig_2();

void UltraSound_Init(uint32_t *p,uint32_t* p2);

float UltraSound_GetVAL();
float UltraSound_GetVAL_2();

#endif //XHB_ULTRASOUND_H
