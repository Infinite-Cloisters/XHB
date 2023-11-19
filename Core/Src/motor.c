#include "motor.h"
#include "tim.h"
#include "oled.h"
#include "GreySensor.h"

_Bool is_1ST_ADC_B = 0;
_Bool is_1ST_ADC_W = 0;
uint32_t CNT_LEN = 0;

//左前
void IN1_2_FWD() {
    GPIOA->BSRR = GPIO_PIN_12 | (GPIO_PIN_11 << 16U);
}
void IN1_2_REV() {
    GPIOA->BSRR = GPIO_PIN_11 | (GPIO_PIN_12 << 16U);
}
//#define IN1_2_FWD() { \
//    GPIOA->BSRR = GPIO_PIN_12 | (GPIO_PIN_11 << 16U); \
//    }
//#define IN1_2_REV() { \
//    GPIOA->BSRR = GPIO_PIN_11 | (GPIO_PIN_12 << 16U); \
//    }

//右前
void IN3_4_FWD() {
    GPIOA->BSRR = GPIO_PIN_10 | (GPIO_PIN_9 << 16U);
}
void IN3_4_REV() {
    GPIOA->BSRR = GPIO_PIN_9 | (GPIO_PIN_10 << 16U);
}
//#define IN3_4_FWD() { \
//    GPIOA->BSRR = GPIO_PIN_10 | (GPIO_PIN_9 << 16U); \
//    }
//#define IN3_4_REV() { \
//    GPIOA->BSRR = GPIO_PIN_9 | (GPIO_PIN_10 << 16U); \
//    }

//左后
void INa_b_FWD() {
    GPIOA->BSRR = GPIO_PIN_8 << 16U;
    GPIOB->BSRR = GPIO_PIN_15;

}
void INa_b_REV() {
    GPIOA->BSRR = GPIO_PIN_8;
    GPIOB->BSRR = GPIO_PIN_15 << 16U;
}
//#define INa_b_FWD() { \
//    GPIOA->BSRR = GPIO_PIN_8 << 16U; \
//    GPIOB->BSRR = GPIO_PIN_15; \
//    }
//#define INa_b_REV() { \
//    GPIOA->BSRR = GPIO_PIN_8; \
//    GPIOB->BSRR = GPIO_PIN_15 << 16U; \
//    }
//右后
void INc_d_FWD() {
    GPIOB->BSRR = GPIO_PIN_13 | (GPIO_PIN_14 << 16U);
}
void INc_d_REV() {
    GPIOB->BSRR = GPIO_PIN_14 | (GPIO_PIN_13 << 16U);
}
//#define INc_d_FWD() { \
//    GPIOB->BSRR = GPIO_PIN_13 | (GPIO_PIN_14 << 16U); \
//    }
//#define INc_d_REV() { \
//    GPIOB->BSRR = GPIO_PIN_14 | (GPIO_PIN_13 << 16U); \
//    }

//制动
void IN_Stop() {
    GPIOA->BSRR = (GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8) << 16U;
    GPIOB->BSRR = (GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13) << 16U;
}
//#define IN_Stop() { \
//    GPIOA->BSRR = (GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8) << 16U; \
//    GPIOB->BSRR = (GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13) << 16U; \
//    }

void IN_L_FWD() {
    IN3_4_FWD();
    INa_b_FWD();
}

void IN_R_FWD() {
    IN1_2_FWD();
    INc_d_FWD();
}

void IN_L_REV() {
    IN3_4_REV();
    INa_b_REV();
}

void IN_R_REV() {
    IN1_2_REV();
    INc_d_REV();
}

//左前PWM
void IN1_2_SPD(uint16_t duty) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty * 30);
}

//右前PWM
void IN3_4_SPD(uint16_t duty) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty * 30);
}

//左后PWM
void INa_b_SPD(uint16_t duty) {
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty * 30);
}

//右后PWM
void INc_d_SPD(uint16_t duty) {
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty * 30);
}

//小车直行
void IN_GoStraight() {
    IN_L_FWD();
    IN_R_FWD();

    IN1_2_SPD(35);
    INa_b_SPD(35);

    IN3_4_SPD(35);
    INc_d_SPD(35);
}

//小车小左转
void IN_TurnLeft() {
    IN_L_REV();
    IN_R_FWD();

    IN1_2_SPD(35);
    INa_b_SPD(35);

    IN3_4_SPD(35);
    INc_d_SPD(35);

}
void IN_TurnRight() {

    IN_L_FWD();
    IN_R_REV();

    IN1_2_SPD(35);
    INa_b_SPD(35);

    IN3_4_SPD(35);
    INc_d_SPD(35);

}
void IN_TurnRight_m() {

    IN_L_FWD();
    IN_R_REV();

    IN1_2_SPD(35);
    INa_b_SPD(35);

    IN3_4_SPD(35);
    INc_d_SPD(35);
    HAL_Delay(100);
}
void IN_TurnLeft_m() {
    IN_R_FWD();
    IN_L_REV();

    IN1_2_SPD(35);
    INa_b_SPD(35);

    IN3_4_SPD(35);
    INc_d_SPD(35);

    HAL_Delay(100);

}
void IN_TurnLeft_l() {

    IN_L_REV();
    IN_R_FWD();

    IN1_2_SPD(50);
    INa_b_SPD(50);

    IN3_4_SPD(50);
    INc_d_SPD(50);
    HAL_Delay(300);
    IN_GoStraight();
    HAL_Delay(20);
}
//小车小右转4



void IN_AI_Control() {
    /* 隧道长度检测
     * [0]->隧道检测
     * [1]~[6]->灰度循迹
     * */

    const int8_t* ADC_R = GreySensor_GetADC();
    //如果隧道检测灰度开启
    if (ADC_R[1] != 0 && is_1ST_ADC_B == 0) {
        //限制仅开启一次
        is_1ST_ADC_B = 1;
        //开始计时
        HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_1);
    }

    if (is_1ST_ADC_W == 0 && ADC_R[1] == 0 && is_1ST_ADC_B == 1) {
        is_1ST_ADC_W = 1;
        HAL_TIM_IC_Stop(&htim1, TIM_CHANNEL_1);
        CNT_LEN = htim1.Instance->CNT;
    }

    /*灰度算法*/
    if(ADC_R[0] ==-9){
        IN_TurnLeft_l();
    }else if(ADC_R[0]==-3){
        IN_TurnLeft_m();
    }else if (ADC_R[0] <=-1){//(-3,-1]
        IN_TurnLeft();
    }else if (ADC_R[0] ==0){//{0}
        IN_GoStraight();
    }else if(ADC_R[0]!=5){//{0}3
        IN_TurnRight();
    }else{
        IN_TurnRight_m();
    }


}