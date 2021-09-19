#ifndef __PID_H
#define __PID_H
#include "sys.h"

typedef struct pid{
    float err;                //定义偏差值
    float err_last;            //定义上一个偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
    float out;          //定义电压值（控制执行器的变量）
    float integral;
		float integral_2; 	//定义积分值
}PID_struct;


extern PID_struct xunji_PID;


float pid(float kp,float ki,float kd,float e);
void PID_Init(PID_struct *PID,float kp,float ki,float kd);
float PID_calc(PID_struct *PID,float e);
#endif

