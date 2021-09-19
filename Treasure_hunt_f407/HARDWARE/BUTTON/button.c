#include "button.h"
#include "delay.h" 
#include "oled.h" 
#include "led.h" 
#include "module.h" 
#include "pid.h" 
#include "trailing.h" 
#include "logic.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//按键输入驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
u8 mode=0;
u8 jg_flag=0;
int temp;
//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
 
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&KEY0==0)
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
	}else if(KEY0==1)key_up=1; 	    
 	return 0;// 无按键按下
}
//void JG_scan()
//{
//	if(step>50)
//	{
//		if(JG==0 && jg_flag==0)
//			jg_flag=1;
//		if(JG==1 && jg_flag==1)
//		{
//			jg_flag=0;
//			mode++;
//		}
//		delay_ms(150);
//		if(mode>3 )
//			mode=0;
//	}
//}
//void oled_show()
//{
//	switch(mode)
//	{
//		case 0:  //正常跑模式
//			if(step<50)
//			{
//				OLED_ShowNum(0,2,all_step,2,16);	
//				OLED_ShowNum(20,2,step,2,16);
//	//			OLED_ShowNum(45,2,angle[2],3,16);
//	//			OLED_ShowNum(80,2,now_yaw,4,16);
//				OLED_ShowNum(20,4,image[0],2,16);
//				OLED_ShowNum(40,4,image[1],2,16);
//				OLED_ShowNum(60,4,image[2],2,16);	
//			}
//			else
//			{
//				OLED_ShowChar(0,0,'s');
//				OLED_ShowChar(10,0,'t');
//				OLED_ShowChar(20,0,'a');
//				OLED_ShowChar(30,0,'r');
//				OLED_ShowChar(40,0,'t');
//				OLED_ShowChar(50,0,' ');
//			}
//			
//			if(KEY0==0)
//			{
//				xunji_flag=10;
//				all_step=0;
//				step=0;
//			}
//			break;
//		
//		case 1:		
//			if(step<50)
//			{
//				OLED_ShowNum(0,2,all_step,2,16);	
//				OLED_ShowNum(20,2,step,2,16);
//			}
//			else
//			{
//			OLED_ShowChar(0,0,'c');
//			OLED_ShowChar(10,0,'i');
//			OLED_ShowChar(20,0,'r');
//			OLED_ShowChar(30,0,'c');
//			OLED_ShowChar(40,0,'l');
//			OLED_ShowChar(50,0,'e');
//			}
//			
//			if(KEY0==0)
//			{
//				hd_flag=0;
//				if(image[0]==3)
//				{
//					xunji_flag=1;
//					all_step=3;
//					step=3;
//				}
//				if(image[0]==4)
//				{
//					xunji_flag=1;
//					all_step=2;
//					step=4;
//				}
//			}
//			break;
//			
//		case 2:		
//			if(step<50)
//			{
//				OLED_ShowNum(0,2,all_step,2,16);	
//				OLED_ShowNum(20,2,step,2,16);
//				OLED_ShowNum(40,2,xunji_flag,2,16);
//			}
//			else
//			{
//				OLED_ShowChar(0,0,'q');
//				OLED_ShowChar(10,0,'x');
//				OLED_ShowChar(20,0,'l');
//				OLED_ShowChar(30,0,'m');
//				OLED_ShowChar(40,0,' ');				
//				OLED_ShowChar(50,0,' ');
//			}
//			if(KEY0==0)
//			{
//				hd_flag=0;
//				xunji_flag=1;
//				all_step=3;
//				step=1;
//			}
//			break;
//	
//		case 3:
//			if(step<50)
//			{
//				OLED_ShowNum(0,2,hd_qian[0],1,16);
//				OLED_ShowNum(12,2,hd_qian[1],1,16);
//				OLED_ShowNum(24,2,hd_qian[2],1,16);
//				OLED_ShowNum(36,2,hd_qian[3],1,16);
//				OLED_ShowNum(48,2,hd_qian[4],1,16);
//				OLED_ShowNum(60,2,hd_qian[5],1,16);		
//				OLED_ShowNum(72,2,hd_qian[6],1,16);
//				OLED_ShowNum(84,2,hd_qian[7],1,16);
//			}
//			else
//			{
//				OLED_ShowChar(0,0,'h');
//				OLED_ShowChar(10,0,'u');
//				OLED_ShowChar(20,0,'i');
//				OLED_ShowChar(30,0,'d');
//				OLED_ShowChar(40,0,'u');
//				OLED_ShowChar(50,0,' ');
//			}
//			if(KEY0==0)
//			{
//				hd_flag=0;
//				all_step=100;
//				step=0;
//			}
//			break;
//				
//	}
//}


