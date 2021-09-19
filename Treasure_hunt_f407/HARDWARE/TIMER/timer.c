#include "timer.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "pid.h"
#include "module.h"
#include "logic.h"
#include "usart.h"
#include "trailing.h"



/**************************************************************************//**
 * 				
 * 				��ʱ���ж�
 * 				
 * 				��Ҫ��������������
 *
 * 
 *
 ******************************************************************************/
 
 
 
 
void TIM2_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}



void TIM5_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}



void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
  {
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־
		
	}
	
}



//��ʱ���жϷ�����
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
  {
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־
    
		get_now_hd();
		get_now_yaw();
		gethdnum();
		
//		

		
if(start==2){		
		all();
	}




//		xunji_Init(99,65);
//		if(flag==0){
//			turn_90('r',1);
//		}
//		else if(flag==1)xunji_Init(0,0);




//		xunji_Init(99,65);
//		if(flag==0){
//			turn_90('r',1);
//		}
//		else if(flag==1)xunji_Init(0,0);


//		xunji_Init(99,65);
//		if(flag==0){
//			turn_90('r',1);
//		}
//		else if(flag==1)xunji_Init(0,0);





//		xunji_Init(99,65);
//		if(flag==0){
//			turn_90('r',1);
//		}
//		else if(flag==1)xunji_Init(0,0);






//		xunji_Init(99,65);
//		nowpingtai=2;
//		if(flag==0){
//			platform(now_yaw);
//		}
////		else if(flag==1)xunji_Init(0,0);





//nowpingtai=3;
//if(kaca!=1)
//GetTreasure();
//else if(image[1]==6)ShakeHead();
	




//xunji_Init(50,now_yaw);






//nowpingtai=3;
//			if(flag==0)platform(now_yaw);
//			else xunji_Init(10,0);
//////        GO7TO8();
//////	
//if(image[1]==6)ShakeHand();
//if(gd2==0&&shakehead_flag==0)ShakeHead();

//if(flag==0)
//ShakeHand();

//     gohome8();




//GO1TO2();

//GO2TO4();

//GO4TO3();


//GO3TO5();


//GO5TO6();//i9�����ΰ� ת90��
//GO6TO7();

//GO7TO8();

	}
}	

