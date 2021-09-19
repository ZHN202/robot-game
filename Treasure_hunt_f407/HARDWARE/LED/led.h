#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
//#define LED0 PBout(8)	// DS0
//#define LED1 PCout(13)	// DS1	 
/*   ǰ�ŻҶ�   PA4--PA7��PC0,1,2,3    */
#define HD1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //PE4
#define HD2 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)	//PE3 
#define HD3 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) //PE2
#define HD4 	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)	//PA0
#define HD5 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) //PE4
#define HD6 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)	//PE3 
#define HD7 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) //PE2
#define HD8 	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)	//PA0
/*   ���ŻҶ�   PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14    */
#define HDH1 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) //PE4
#define HDH2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)	//PE3 
#define HDH3 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9) //PE2
#define HDH4 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)	//PA0
#define HDH5 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11) //PE4
#define HDH6 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)	//PE3 
#define HDH7 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) //PE2
#define HDH8 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)	//PA0
/*     ����Ҷ�      */
#define HDR 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6) //PE2     SB4
#define HDL 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8) //        SB5
/*       �������       */
#define DIR1 PCout(11)	// ��
#define DIR2 PCout(10)	//			in4
#define DIR3 PCout(12)	// ��
#define DIR4 PCout(4)	// 					in1				
/*       ǰɫ��      */
#define SBR 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) //        SB1
#define SBL 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) //        SB2
/*        �����Ĺ�翪��      */
#define GD1 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5) //        SB3
#define GD2 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9) //        SB6
/*       ����    */
#define JG 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)  //        JG1
/*       ͼ��      */
#define IMG 	  PDout(2)



void HUIDU_Init(void);
void LED_Init(void);//��ʼ��
void DIR_Init(void);

#endif