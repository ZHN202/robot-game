#include "sys.h"
#include "usart.h"	
#include "string.h"
#include "module.h"

int counter;
double angle[3];

u32 X,x,Y,y,Z,z;	
////////////////////////////////////////////////////////////////////////////////// 	 
//????ucos,???????????.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ??	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//?????????,??????,??????????
//ALIENTEK STM32???
//??1???		   


//////////////////////////////////////////////////////////////////
//??????,??printf??,??????use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//??????????                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//??_sys_exit()??????????    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//???fputc?? 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//????,??????   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
#if EN_USART1_RX   //???????
//??1??????
//??,??USARTx->SR??????????   	
u8 USART_RX_BUF[USART_REC_LEN];     //????,??USART_REC_LEN???.
//????
//bit15,	??????
//bit14,	???0x0d
//bit13~0,	??????????
u16 USART_RX_STA=0;       //??????	  
  
void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART1，GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//USART1_TX   GPIOA.9
	
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10
	
	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 

	
	//USART_ClearFlag(USART3, USART_FLAG_RXNE);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
}
void uart3_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOA10复用为USART1
	
//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PA9，PA10
	
  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口1 

}


u8 img_num=0;
int ii=0;
extern u8 image[3];
void USART3_IRQHandler(void)                  	//??1??????
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{

		
		Res=USART_ReceiveData(USART3);//(USART1->DR);	//读取接收到的数据 
		
		ii=USART_ReceiveData(USART3);
		if(img_num==0)
		{
//			if(image[img_num]==0)
//				image[img_num]=Res-48;
			if(nowpingtai==2&&(Res-48==3||Res-48==4))image[0]=Res-48;
			if((nowpingtai==3||nowpingtai==4)&&(Res-48==5||Res-48==6))image[1]=Res-48;
			if((nowpingtai==5||nowpingtai==6)&&(Res-48==7||Res-48==8))image[2]=Res-48;
//			Res=0;

		}
	
		
  } 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 


	
void USART2_IRQHandler(void)                	//??1??????
{
	  u8 Res;
#if SYSTEM_SUPPORT_OS 		//??SYSTEM_SUPPORT_OS??,?????OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //????(?????????0x0d 0x0a??)
	{
			Res =USART_ReceiveData(USART2);
			USART_RX_BUF[counter]=Res ;
			if(USART_RX_BUF[0]!=0x3A) 
			return; 
			counter++;
			if(counter==53)             
		{
			counter=0; 
			z=USART_RX_BUF[41];
			Z=USART_RX_BUF[42];
			y=USART_RX_BUF[37];
			Y=USART_RX_BUF[38];
			x=USART_RX_BUF[39];
			X=USART_RX_BUF[40];
		
//	if(GYRO.flag==1)
//		{
//		 Angle[2]=(Z<<8)|z;
//    if(Angle[2]<=31415)
//      Angle[2]=Angle[2]/31415.00*180.00;
//    if(Angle[2]>=34121)
//	    Angle[2]=(31415-65536+Angle[2])/31415.00*180+180;
//		GYRO.Z_dv=GYRO.Z_last-Angle[2];
//		if(GYRO.Z_dv>=300&&GYRO.Z_last<=360&&GYRO.Z_last>=330&&Angle[2]>=0&&Angle[2]<=30)
//		{
//			GYRO.Z_high++;
//		}
//		if(GYRO.Z_dv<=-300&GYRO.Z_last<=30&&GYRO.Z_last>=0&&Angle[2]>=330&&Angle[2]<=360)
//		{
//			GYRO.Z_high--;
//		}

//		GYRO.Z_last=Angle[2];
//		Angle[2]=GYRO.Z_high*360+Angle[2]-GYRO.Z_save;
//		///////////////////////////////////////////////
//		Angle[1]=(Y<<8)|y;
//    if(Angle[1]<=31415)
//      Angle[1]=Angle[1]/31415.00*180.00;
//    if(Angle[1]>=34121)
//	    Angle[1]=(31415-65536+Angle[1])/31415.00*180+180;
//		GYRO.Y_dv=GYRO.Y_last-Angle[1];
//		
//	if(GYRO.Y_dv>=300&&GYRO.Y_last<=360&&GYRO.Y_last>=330&&Angle[1]>=0&&Angle[1]<=30)
//		{
//			GYRO.Y_high++;
//		}
//		if(GYRO.Y_dv<=-300&GYRO.Y_last<=30&&GYRO.Y_last>=0&&Angle[1]>=330&&Angle[1]<=360)
//		{
//			GYRO.Y_high--;
//		}

//		GYRO.Y_last=Angle[1];
//		Angle[1]=GYRO.Y_high*360+Angle[1]-GYRO.Y_save;
//	  ///////////////////////////////////////////////
//		Angle[0]=(X<<8)|x;
//    if(Angle[0]<=31415)
//      Angle[0]=Angle[0]/31415.00*180.00;
//    if(Angle[0]>=34121)
//	    Angle[0]=(31415-65536+Angle[0])/31415.00*180+180;
//		
//			GYRO.X_dv=GYRO.X_last-Angle[0];
//		if(GYRO.X_dv>=300&&GYRO.X_last<=360&&GYRO.X_last>=330&&Angle[0]>=0&&Angle[0]<=30)
//		{
//			GYRO.X_high++;
//		}
//		if(GYRO.X_dv<=-300&GYRO.X_last<=30&&GYRO.X_last>=0&&Angle[0]>=330&&Angle[0]<=360)
//		{
//			GYRO.X_high--;
//		}

//		GYRO.X_last=Angle[0];
//		Angle[0]=GYRO.X_high*360+Angle[1]-GYRO.X_save;
//	}
	
//	else if(GYRO.flag==0)
//	{ 
		  angle[2]=(Z<<8)|z;
    if(angle[2]<=31415)
      angle[2]=angle[2]/31415.00*180.00;
    if(angle[2]>=34121)
	    angle[2]=(31415-65536+angle[2])/31415.00*180+180;
		 angle[1]=(Y<<8)|y;
    if(angle[1]<=31415)
      angle[1]=angle[1]/31415.00*180.00;
    if(angle[1]>=34121)
	    angle[1]=(31415-65536+angle[1])/31415.00*180+180;
		 angle[0]=(X<<8)|x;
    if(angle[0]<=31415)
      angle[0]=angle[0]/31415.00*180.00;
    if(angle[0]>=34121)
	    angle[0]=(31415-65536+angle[0])/31415.00*180+180;
//	}
	 
		///////////////////////////////////////
		
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	};  											 

} 
#endif

