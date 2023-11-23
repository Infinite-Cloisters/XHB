//
// Created by 28035 on 2023/11/11.
//

#include "UltraSound.h"
#include "stdio.h"


#define Trigger_GPIO_Port GPIOB
#define Trigger_Pin GPIO_PIN_12


#define Trigger_GPIO_Port_2 GPIOC
#define Trigger_Pin_2 GPIO_PIN_13
volatile float UltraSound_VAL=0;
volatile float UltraSound_VAL_2=0;
volatile uint32_t *cnt;
volatile uint32_t *cnt_2;

void UltraSound_Init(uint32_t* p,uint32_t* p2){
    cnt = p;
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
void UltraSound_SendTrig_2(){
    HAL_GPIO_WritePin(Trigger_GPIO_Port_2,Trigger_Pin_2,GPIO_PIN_SET);
    HAL_Delay_us(15);
    HAL_GPIO_WritePin(Trigger_GPIO_Port_2,Trigger_Pin_2,GPIO_PIN_RESET);
}
//CNT -> us

float UltraSound_GetVAL(){
    if(*cnt!=0xFFFF && *cnt!=0) {
        UltraSound_VAL = (float) *cnt * 173 / 1000;
        return UltraSound_VAL;
    }
    else
        return 0;
    //

}

float UltraSound_GetVAL_2(){
    if(*cnt_2!=0xFFFF && *cnt_2!=0) {
        UltraSound_VAL_2 = (float) *cnt_2 * 173 / 1000;
        printf("%f\n",UltraSound_VAL_2);
        return UltraSound_VAL_2;
    }
    else
        return 0;
}