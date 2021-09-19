#ifndef __TRAILING_H
#define __TRAILING_H
#include "sys.h"

extern unsigned char Re_buf[11],temp_buf[11],counter;
extern unsigned char sign,t,he;
extern  unsigned char Temp[11];
extern double angle[3];



void colorcode_go_straight(int speed);
void right_single2(int speed);
void left_single2(int speed);

void get_now_hd(void);
void left(int speed);
void right(int speed);
void right_single(int speed);
void left_single(int speed);
void forward(void);
void stop(void);
void goback(void);
void gethdnum(void);
void error(void);
void right_high_speed(int speed);
void left_high_speed(int speed);
void xunji(unsigned int speed);
int get_now_yaw(void);
void mpu_go_straight(int yaw_set);
void 	huidu_go_straight2(void);
void goforward(int speed2);
void xunji_high_speed(unsigned int speed);
void stop_snub(int s_time,char aim_speed_mode);
void xunji_Init(u8 mode,u8 xunji_gear);
void xunji_ing(u8 mode1);
void xunji_start(int aim_speed);
extern u8 xunji_flag,xunji_gear;  
extern u8 hd_qian[8],hd_hou[8],hwleft,hwright,hdl,jg,sbr;
extern float error_all,error_qian,error_hou,eq[8],eh[8];
extern float out,out_left,out_right,out_left_last;
extern u8 huidu_qian_num,huidu_hou_num,xunji_gear;
extern int h,sum1;
extern int stop_time,speed_d;
extern int error_yaw,now_yaw;
extern int adcx1,adcx2;	
extern int gd1,gd2;	
#endif
