#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED端口定义
//#define LED0 PBout(8)	// DS0
//#define LED1 PCout(13)	// DS1	 
/*   前排灰度   PA4--PA7，PC0,1,2,3    */
#define HD1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //PE4
#define HD2 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)	//PE3 
#define HD3 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) //PE2
#define HD4 	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)	//PA0
#define HD5 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) //PE4
#define HD6 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)	//PE3 
#define HD7 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) //PE2
#define HD8 	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)	//PA0
/*   后排灰度   PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14    */
#define HDH1 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) //PE4
#define HDH2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)	//PE3 
#define HDH3 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9) //PE2
#define HDH4 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)	//PA0
#define HDH5 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11) //PE4
#define HDH6 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)	//PE3 
#define HDH7 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) //PE2
#define HDH8 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)	//PA0
/*     侧面灰度      */
#define HDR 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6) //PE2     SB4
#define HDL 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8) //        SB5
/*       电机驱动       */
#define DIR1 PCout(11)	// 右
#define DIR2 PCout(10)	//			in4
#define DIR3 PCout(12)	// 左
#define DIR4 PCout(4)	// 					in1				
/*       前色标      */
#define SBR 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) //        SB1
#define SBL 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) //        SB2
/*        出发的光电开关      */
#define GD1 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5) //        SB3
#define GD2 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9) //        SB6
/*       激光    */
#define JG 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)  //        JG1
/*       图像      */
#define IMG 	  PDout(2)



void HUIDU_Init(void);
void LED_Init(void);//初始化
void DIR_Init(void);

#endif