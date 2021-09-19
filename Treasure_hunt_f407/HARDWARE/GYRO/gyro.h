#ifndef __GYRO_H
#define __GYRO_H	
#include "sys.h"


void GYRO_Calc(void);//Õ”¬›“«º∆À„
void GYRO_Init(void);//Õ”¬›“«≥ı ºªØ
float RANGE (float a);
void ANGLEY(void);
void ANGLEZ(void);
void ANGLEX(void);
void jilujiaodu1(void);
void jilujiaodu2(void);
void jilujiaodu3(void);
float anerr1 ( float yvding);
float anerr2 ( float yvding);
void anpid1 ( float yvding , float p ,float i,float d );
void anpid2 ( float yvding , float p ,float i,float d );
void xuanzhuan( float yvding );
void xuanzhuan2( float yvding );
//void tlPID ( float yvding );
void tlxj( float yvding );
//void qiaoPID ( float yvding );
void xqiao( float yvding );
void zaxj( float yvding );
void lkxj( float yvding );



	 				    
#endif
