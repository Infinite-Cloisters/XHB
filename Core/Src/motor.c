#include "motor.h"
#include "tim.h"
#include "oled.h"
#include "GreySensor.h"
#include "UltraSound.h"
#include "stdio.h"

volatile _Bool is_1ST_ADC_B = 0;
volatile _Bool is_1ST_ADC_W = 0;
uint32_t CNT_LEN = 0;
volatile char *ptr_flag;
volatile char *ptr_flag_2;

void IN_Init(char *p, char *p_2) {
    ptr_flag = p;
    ptr_flag_2 = p_2;
}

void UltraSound_Evadible();

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

    IN1_2_SPD(25);
    INa_b_SPD(25);

    IN3_4_SPD(25);
    INc_d_SPD(25);
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

    HAL_Delay(300);

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

void IN_TurnRight_l() {

    IN_L_FWD();
    IN_R_REV();

    IN1_2_SPD(45);
    INa_b_SPD(45);

    IN3_4_SPD(45);
    INc_d_SPD(45);
    HAL_Delay(100);
}


void IN_AI_Control() {
    /* 隧道长度检测
     * [0]->隧道检测
     * [1]~[6]->灰度循迹
     * */
    //UltraSound_Evadible();

    const int8_t *ADC_R = GreySensor_GetADC();
    //如果隧道检测灰度开启

    if (ADC_R[1] != 0 && is_1ST_ADC_B == 0) {
        printf("BEGIN\n");
        //限制仅开启一次
        is_1ST_ADC_B = 1;
        //开始计时
        HAL_TIM_Base_Start(&htim5);
    }
    OLED_ShowNum(0,28, ADC_R[1],1,12,1);
    OLED_Refresh();
    if (is_1ST_ADC_W == 0 && ADC_R[1] == 0 && is_1ST_ADC_B == 1) {
        is_1ST_ADC_W = 1;
        HAL_TIM_Base_Stop(&htim5);
        printf("STOP\n");
        CNT_LEN = htim5.Instance->CNT;

        OLED_ShowNum(0,0, CNT_LEN,4,12,1);
        OLED_Refresh();
    }
    ADC_R = GreySensor_GetADC();
    /*灰度算法*/
//    if (ADC_R[0] == -9) {
//        IN_TurnLeft_l();
//        return;
//    }
//    ADC_R = GreySensor_GetADC();
//    if (ADC_R[0] <= -3) {
//        IN_TurnLeft_m();
//        return;
//    }
//    ADC_R = GreySensor_GetADC();
//    if (ADC_R[0] <= -1) {//(-3,-1]
//        IN_TurnLeft();
//        return;
//    }
//    ADC_R = GreySensor_GetADC();
//    if (ADC_R[0] == 0) {//{0}
//        IN_GoStraight();
//        return;
//    }
//    ADC_R = GreySensor_GetADC();
//    if (ADC_R[0] != 5) {//{0}3
//        IN_TurnRight();
//        return;
//    }
//    IN_TurnRight_m();

}

/*超声波避障*/

void UltraSound_Evadible() {
    /*当小车与障碍物距离小于
     * 设置的最小距离MIN_DIS并制动后
     * 小车向左转避开障碍物
     * 后向右转并直行根据障碍物大小设定的直行时间GoStraight_Time
     * 后右转直到灰度检测到循迹线后回正
     */
    printf("%d\t%d\n",*ptr_flag,*ptr_flag_2);
    if (*ptr_flag == 2) {
        float DIS = UltraSound_GetVAL();
        if (DIS <= 16 && DIS >= 13) {
            IN_Stop();
            HAL_Delay(500);
            IN_TurnLeft_l();
            HAL_Delay(800);
            IN_TurnRight_l();
            HAL_Delay(500);
            IN_GoStraight();
            HAL_Delay(550);
            IN_TurnRight_l();
            HAL_Delay(500);
        }
        *ptr_flag = 0;
        UltraSound_SendTrig();
    }

    if (*ptr_flag_2 == 2) {
        float DIS_2 = UltraSound_GetVAL_2();
        if (DIS_2 <= 16 && DIS_2 >= 13) {
            IN_Stop();
            HAL_Delay(5000);
        }
        *ptr_flag_2 = 0;
        UltraSound_SendTrig_2();
    }
}

