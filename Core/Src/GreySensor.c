#include "GreySensor.h"
#include "stdio.h"

int32_t ADC_MID[7] = {0};
int32_t ADC_MID_PCT5[7] = {0};
_Bool ADC_RESULT[7] = {0};
int8_t RET[2] = {0};
uint16_t *pADC;
#define ADC_N 20

int cmp(const void *a, const void *b) {
    int16_t c = *(int16_t *) a;
    int16_t d = *(int16_t *) b;
    return c - d;
}

void GreySensor_Init(uint16_t *Array) {
    pADC = Array;
    //采样 ADC_N 次，中值滤波
    int16_t ADC_TMP[7][ADC_N] = {0};
    uint8_t i = 0;
    uint8_t j = 0;
    for (; i < ADC_N; ++i) {
        for (j = 0; j < 7; ++j)
            ADC_TMP[j][i] = (int16_t) Array[j];
        HAL_Delay(15);
    }
    for (i = 0; i < 7; ++i) {
        qsort(ADC_TMP[i], ADC_N, sizeof(int16_t), cmp);
        ADC_MID[i] = (ADC_TMP[i][9] + ADC_TMP[i][10]) / 2;
        ADC_MID_PCT5[i] = ADC_MID[i] / 20;
    }
    for (i = 1; i < 7; ++i) {
        printf("%ld\t", ADC_MID[i]);
    }
}

/*对adc数值进行处理
 * 1->B 0->W 返回一个_Bool数组
 * 如果波动大于10%则认为是黑色
 * 第一个值为朝天灰度
 * 其他为循迹灰度
 * 这个接口由motor调用
 * */

int8_t* GreySensor_GetADC() {

    int8_t Base = -5;
    for (uint8_t i = 0; i < 7; ++i) {
        if ((int32_t) pADC - ADC_MID[i] > ADC_MID_PCT5[i]) {
            ADC_RESULT[i] = 1;
            RET[0] += Base;
        }
        Base += 2;
    }
    return RET;
}

#undef ADC_N