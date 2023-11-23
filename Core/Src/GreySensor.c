#include "GreySensor.h"
#include "stdio.h"
#include "adc.h"
#include "oled.h"

_Bool ADC_RESULT[7] = {0};
int8_t RET[2] = {0};
uint16_t *pADC ;

int cmp(const void *a, const void *b) {
    int16_t c = *(int16_t *) a;
    int16_t d = *(int16_t *) b;
    return c - d;
}

void GreySensor_Init(uint16_t *Array) {
    pADC   =  Array;
}

/*对adc数值进行处理
 * 1->B 0->W 返回一个_Bool数组
 * 如果波动大于10%则认为是黑色
 * 第一个值为朝天灰度
 * 其他为循迹灰度
 * 这个接口由motor调用
 * */
void GreySensor_Update() {
    uint8_t index = 0;
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,50);
    OLED_ShowNum(0,12,hadc1.Instance->DR,4,12,1);
    OLED_Refresh();
    if (hadc1.Instance->DR > 4000) {
        pADC[index++] = 1;
    } else {
        pADC[index++] = 0;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET) {
        pADC[index++] = 1;
    } else {
        pADC[index++] = 0;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET) {
        pADC[index++] = 1;
    } else {
        pADC[index++] = 0;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET) {
        pADC[index++] = 1;
    } else {
        pADC[index++] = 0;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET) {
        pADC[index++] = 1;
    } else {
        pADC[index++] = 0;
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_SET) {
        pADC[index++] = 1;
    } else {
        pADC[index++] = 0;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET) {
        pADC[index++] = 1;
    } else {
        pADC[index++] = 0;
    }
}
int8_t *GreySensor_GetADC() {
    GreySensor_Update();
    RET[0] = 0;
    RET[1] = pADC[0];
    int8_t Base = -5;

    for (uint8_t i = 1; i < 7; ++i) {
        if (pADC[i]==1) {
            RET[0] += Base;
        }
        Base+= 2;
    }
    return RET;
}

#undef ADC_N