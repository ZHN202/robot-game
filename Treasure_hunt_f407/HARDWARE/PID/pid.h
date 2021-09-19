#ifndef __PID_H
#define __PID_H
#include "sys.h"

typedef struct pid{
    float err;                //����ƫ��ֵ
    float err_last;            //������һ��ƫ��ֵ
    float Kp,Ki,Kd;            //������������֡�΢��ϵ��
    float out;          //�����ѹֵ������ִ�����ı�����
    float integral;
		float integral_2; 	//�������ֵ
}PID_struct;


extern PID_struct xunji_PID;


float pid(float kp,float ki,float kd,float e);
void PID_Init(PID_struct *PID,float kp,float ki,float kd);
float PID_calc(PID_struct *PID,float e);
#endif

