//
// Created by 28035 on 2023/11/11.
//

#include "UltraSound.h"
#include "stdio.h"


#define Trigger_GPIO_Port GPIOB
#define Trigger_Pin GPIO_PIN_12

float UltraSound_VAL;
uint32_t *cnt;
char *ptr_flag;

void UltraSound_Init(uint32_t* p,char *p_flag){
    cnt = p;
    ptr_flag = p_flag;
}


void HAL_Delay_us(__IO uint16_t Delay){
    Delay*=10;
    do {
        __asm volatile("NOP");
        __asm volatile("NOP");
        __asm volatile("NOP");
        __asm volatile("NOP");
        __asm volatile("NOP");

        __asm volatile("NOP");
        __asm volatile("NOP");
        __asm volatile("NOP");
        __asm volatile("NOP");
        __asm volatile("NOP");

    } while (Delay--);
}

void UltraSound_SendTrig(){
    Trigger_GPIO_Port->BSRR = Trigger_Pin;
    HAL_Delay_us(15);
    Trigger_GPIO_Port->BSRR= Trigger_Pin << 16U;
}

//CNT -> us
uint32_t t;
float UltraSound_GetVAL(){
    *ptr_flag=0;
    *cnt=0;
    t=0;

    UltraSound_SendTrig();

    while(*ptr_flag!=2&&t<65535){
        ++t;
    }

    if(*cnt!=0xFFFF && *cnt!=0)
        UltraSound_VAL = (float)*cnt * 173 /10000;
    else
        return 0;
    return UltraSound_VAL;
}