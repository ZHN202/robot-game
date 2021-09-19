#include "module.h"
#include "pid.h"
#include "trailing.h"

PID_struct xunji_PID;



float pid(float kp,float ki,float kd,float e)
{
	static float sum=0,e_l=0;
	float e_n,r;
	e_n=e;
	sum+=e_n;
	if((e_n==0)||((e_n>0)&&(e_l<0))||((e_n<0)&&(e_l>0)))
		sum=0;
	if(sum>100)
		sum=100;
	if(sum<-100)
		sum=-100;
	e_l=e_n-e_l;
	r=kp*e_n+ki*sum+kd*e_l;
	e_l=e_n;
	return r;
}
void PID_Init(PID_struct *PID,float kp,float ki,float kd)//初始化PID结构体参数
{
	PID->Kp = kp;
	PID->Ki = ki;
	PID->Kd = kd;
}

float PID_calc(PID_struct *PID,float e)
{
	PID->err =e;
		
	if(PID->err>=(float)1.5 || PID->err <=(float)-1.5)
	{
		PID->integral += PID->err;
	}
	else
	{
		PID->integral=0;
		PID->integral_2 += PID->err;
	}
	if(PID->integral >= 100)
		PID->integral = 100;
	if(PID->integral <= -100)
		PID->integral = -100;
	if(PID->integral_2 >= 30)
		PID->integral_2 = 30;
	if(PID->integral_2 <= -30)
		PID->integral_2 = -30;
	if((PID->err<=(float)1.5 && PID->err>=(float)-1.5))
		PID->out = PID->Kp * PID->err + PID->Ki * PID->integral_2 + PID->Kd *( PID->err - PID->err_last );
	else
		PID->out = PID->Kp * PID->err + PID->Ki * PID->integral + PID->Kd *( PID->err - PID->err_last );
	PID->err_last = PID->err;
	return PID->out;
}

