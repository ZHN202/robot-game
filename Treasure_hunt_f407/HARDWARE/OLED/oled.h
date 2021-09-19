//////////////////////////////////////////////////////////////////////////////////	 

//********************************************************************************

//STM32FXX核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/



#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	 

#include "stm32f4xx.h"

//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
		    						  
//-----------------OLED端口定义----------------  					   

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_12)


#define OLED_RS_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_6)//RS
#define OLED_RS_Set() GPIO_SetBits(GPIOC,GPIO_Pin_6)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_14)//复位信号设置为低
#define OLED_RST_Set() GPIO_SetBits(GPIOB, GPIO_Pin_14)  //复位信号设置为高

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//硬件驱动接口
void SPI2_Init(void);
unsigned char SPI2_ReadWriteByte(unsigned char TxData);


//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

#endif  
	 



