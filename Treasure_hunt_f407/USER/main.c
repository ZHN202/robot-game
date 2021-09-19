#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "pwm.h"
#include "timer.h"
#include "string.h"
#include "button.h"
#include "pid.h"
#include "module.h"
#include "trailing.h"
#include "logic.h"




/**************************************************************************//**
 * 				��ʱ��3��
 * 				ͨ��3:�� DR1 DR2 :��ת:0 1 �ƶ�: 0 0
 * 				ͨ��4:�� DR3 DR4 :��ת:0 1 �ƶ�: 0 0
 * 				
 *				�Ҷ�7Ϊ���Ҳ�
 * 				�Ҷ�0Ϊ�����
 *
 ******************************************************************************/

/*


*/

u8 image[3]={0,0,0};  // image[0] 3��4    image[1] 5��6    image[2] 7��8
extern unsigned char sign,t,he;
extern double angle[3];
u8 key;
extern int temp;



int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	

	uart2_init(115200);
	uart3_init(115200);
	
	delay_init(168);		  
	
  DIR_Init(); 
	KEY_Init();
	HUIDU_Init();
//	Adc_Init(); 
	
	IMG=0;

	
	OLED_Init();
	OLED_Clear();
	
	TIM2_Int_Initl(5000-1,84-1); //5ms//	500  840
//	TIM5_Int_Initl(500-1,840-1); //5ms//	500  840
	
	TIM3_PWM_Init(1000-1,84-1);    
	
	TIM4_PWM_Init(1000-1,1680-1);    
	//ͷ 50 ����50 ���� 145
	TIM_SetCompare2(TIM4,50);//ͷ
	TIM_SetCompare3(TIM4,45);//����
	TIM_SetCompare4(TIM4,90);//����
	//תͷ 75 ̧����75 ̧���� 90

		get_now_hd();
		get_now_yaw();
		gethdnum();
//		LED_Init();

	while(1){
	  
	if(HDL==0&&HDR==0&&gd1==0&&start==0){start = 1;}
	
	//left(50);
		
		get_now_hd();
		get_now_yaw();
		gethdnum();
//    OLED_ShowNum(60,2,step,2,16);
//		OLED_ShowNum(80,2,Step,2,16);
//	  OLED_ShowNum(100,2,flag,2,16);
//		OLED_ShowNum(20,6,huidu_qian_num,2,16);
	
	
		if(start==1&&gd1==1)start=2;
		if(start==2)xunji_ing(xunji_flag);
	
	//if(KEY_Scan(1))xunji_ing(xunji_flag);
//		if(gd1==0)start=1;
//		if(KEY_Scan(1)){ USART_SendData(USART3, 0x6B);start=0;}
//		if(image[0]==7)TIM_SetCompare2(TIM4,100);;
		
		
		
	}
}
