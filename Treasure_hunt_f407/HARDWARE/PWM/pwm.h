#ifndef _PWM_H
#define _PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM2_PWM_Init(u32 arr,u32 psc);
void TIM1_PWM_Init(u32 arr,u32 psc);
void TIM4_PWM_Init(u32 arr,u32 psc);
void robot_control(int mode);
#endif
