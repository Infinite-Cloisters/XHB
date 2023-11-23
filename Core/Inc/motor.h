#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"

void IN_Init(char *p,char *p_2);

//void IN1_2_FWD();
//void IN1_2_REV();
void IN1_2_SPD(uint16_t duty);

//void IN3_4_FWD();
//void IN3_4_REV();
void IN3_4_SPD(uint16_t duty);

//void INa_b_FWD();
//void INa_b_REV();
void INa_b_SPD(uint16_t duty);

//void INc_d_FWD();
//void INc_d_REV();
void INc_d_SPD(uint16_t duty);

void IN_L_FWD();
void IN_R_FWD();
void IN_L_REV();
void IN_R_REV();

void IN_Stop();

void IN_AI_Control();

#endif