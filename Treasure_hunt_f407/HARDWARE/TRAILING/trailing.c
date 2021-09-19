#include "trailing.h"
#include "led.h"
#include "delay.h"
#include "module.h"
#include "pid.h"
#include "logic.h"
int h;
u8 hd_qian[8]={1,1,1,1,1,1,1,1},hd_hou[8]={1,1,1,1,1,1,1,1},hwleft=0,hwright=0,hdl=0,sbr=0;//前后排灰度检测到白线的状态 
float error_all=0,error_qian=0,error_hou=0,eq[8]={-8,-4,-2,-1,1,2,4,8},eh[8]={8,5,2,1,-1,-2,-5,-8};
float out,out_left,out_right,out_left_last;
int sum1=0;
u8 huidu_qian_num=0,huidu_hou_num=0;//huidu_qian_num 前排灰度检测到白线的数量  huidu_hou_num 后排灰度检测到白线的数量
u8 xunji_flag=1,xunji_gear=0;
int error_yaw,now_yaw=0;
int stop_time=0;
int speed_d=0;	
int gd1,gd2;
	
	
void get_now_hd(){
		hd_qian[0]=HD1;
		hd_qian[1]=HD2;
		hd_qian[2]=HD3;
		hd_qian[3]=HD4;
		hd_qian[4]=HD5;
		hd_qian[5]=HD6;
		hd_qian[6]=HD7;
		hd_qian[7]=HD8;
	
		hd_hou[0]=HDH1;
		hd_hou[1]=HDH2;
		hd_hou[2]=HDH3;
		hd_hou[3]=HDH4;
		hd_hou[4]=HDH5;
		hd_hou[5]=HDH6;
		hd_hou[6]=HDH7;
		hd_hou[7]=HDH8;
		gd1=GD1;
		gd2=GD2;
		hwleft=HDL;
		hwright=HDR;
		hdl=HDL;
		sbr=SBR;
}
void left_high_speed(int speed){
	speed_d+=4;
	speed=speed-speed_d;
	if(speed<=100)
		speed=100;
	DIR1=0;
	DIR2=1;
	DIR3=1;
	DIR4=0;
	TIM_SetCompare3(TIM3,speed);//you
	TIM_SetCompare4(TIM3,speed*1.02);//1.1
}
void right_high_speed(int speed){
	speed_d+=4;
	speed=speed-speed_d;
	if(speed<=100)
		speed=100;
	DIR1=1;
	DIR2=0;
	DIR3=0;
	DIR4=1;
	TIM_SetCompare3(TIM3,speed);//you
	TIM_SetCompare4(TIM3,speed*1.02);//1.1
}
void left(int speed){
	DIR1=0;
	DIR2=1;
	DIR3=1;
	DIR4=0;
	TIM_SetCompare3(TIM3,speed);//you
	TIM_SetCompare4(TIM3,speed*1.1);//1.1
}
void right(int speed){
	DIR1=1;
	DIR2=0;
	DIR3=0;
	DIR4=1;
	TIM_SetCompare3(TIM3,speed);
	TIM_SetCompare4(TIM3,speed);
}
void left_single(int speed){
	DIR1=0;
	DIR2=1;//y
	
	DIR3=1;
	DIR4=0;
	TIM_SetCompare3(TIM3,0);//you
	TIM_SetCompare4(TIM3,speed);//1.1
}
void right_single(int speed){
	DIR1=1;
	DIR2=0;//y
	
	DIR3=0;
	DIR4=1;
	TIM_SetCompare3(TIM3,speed);
	TIM_SetCompare4(TIM3,0);
}

void goforward(int speed2){
	DIR1=0;
	DIR2=1;
	DIR3=0;
	DIR4=1;
	TIM_SetCompare3(TIM3,speed2);//you //250 1.10  //220 1.07  //230 1.08 
	TIM_SetCompare4(TIM3,speed2*1.1);
}
void forward(){
	DIR1=0;
	DIR2=1;
	DIR3=0;
	DIR4=1;
}
void stop(){
	DIR1=0;
	DIR2=0;
	DIR3=0;
	DIR4=0;
}
void goback(){
	DIR1=1;
	DIR2=0;
	DIR3=1;
	DIR4=0;
	TIM_SetCompare3(TIM3,80);//you //250 1.10  //220 1.07  //230 1.08 
	TIM_SetCompare4(TIM3,80);
}
//点刹
void stop_snub(int s_time,char aim_speed_mode){

	if(stop_time<s_time)
	{
		xunji_Init(0,0);
		stop_time++;	
		switch(aim_speed_mode)
		{
			case 'p':				//平台
				if(stop_time%2==1)
					stop();		
				else
					left(200);
				break;
			
			case 'l':			//直线转弯
				if(stop_time%2==1)
					stop();		
				else
					xunji(40);
				break;
				
			case 'h':		//高速
				if(stop_time%5==1)
					stop();		
				else
					
				xunji(120);		
				break;
		}
	}
	else
	{
		switch(aim_speed_mode)
		{
			case 'p':				//平台
				left(80);
				xunji_Init(0,0);
				break;
			
			case 'l':			//直线转弯
				if(nowpingtai==6)
					xunji_Init(2,0);
				else
					goforward(65);
				break;
				
			case 'h':		//高速
				xunji_Init(1,0);
				stop_time=0;
				speed_step++;			
				break;
		}
		
	}
	
}

//获取灰度值·
void gethdnum(){
	huidu_qian_num=0;
	huidu_hou_num=0;
	for(h=0;h<8;h++)
	{
		if(hd_qian[h]==0)
		{
			huidu_qian_num++;
		}
		if(hd_hou[h]==0)
		{
			huidu_hou_num++;
		}
	}
}

void xunji_start(int aim_speed){
	static int now_speed=80;
	if(xunji_flag!=0)xunji_Init(0,0);
	
	now_speed+=3;
	
	if(now_speed<=200)
		xunji(now_speed);
	else
		xunji_high_speed(now_speed);

	if(now_speed>=aim_speed)
	{
		now_speed=80;
		speed_step++;
	}
}





// 误差
void error(){
	
	
	static int i=0,j=0;
	
	
	error_qian=0;          //前排误差
	error_hou=0;           //后排误差
	
	
	if(huidu_qian_num<=1)
	{
		for(h=0;h<8;h++)
			if(hd_qian[h]==0)
				error_qian+=eq[h];
	}
	
	else 
	{
		for(h=0;h<4;h++)
		{
			if(hd_qian[h]==0)     //从左往右找白线
				i=h;
			if(hd_qian[7-h]==0)   //从右往左找白线
				j=7-h;
		}
    if((i!=-1)&&(j==-1))         //左边四个灰度检测到白线   右偏
			error_qian=eq[i]+eq[i-1];
		else if((j!=-1)&&(i==-1))    //右边四个灰度检测到白线   左偏
			error_qian=eq[j]+eq[j+1];
		else if(((j!=-1)&&(i!=-1)))  //左边右边都检测到白线
		{
			if(j>7-i)   // 右偏               
				error_qian=eq[i]+eq[i-1];
			else if(j==7-i)   //无偏差
				error_qian=0;
			else
				error_qian=eq[j]+eq[j+1];
		}
		else 
			error_qian=0;
		i=-1;
		j=-1;
	}
	
	
	
//	if(huidu_hou_num<=1)
//		for(h=0;h<8;h++)
//		{
//			if(hd_hou[h]==0)
//			{
//				error_hou+=eh[h];
//			}
//		}
//	else
//	{
//		for(h=0;h<4;h++)
//		{
//			if(hd_hou[h]==0)
//				i=h;
//			if(hd_hou[7-h]==0)
//				j=7-h;
//		}
//    if((i!=-1)&&(j==-1))
//			error_hou=eh[i]+eh[i-1];
//		else if((j!=-1)&&(i==-1))
//			error_hou=eh[j]+eh[j+1];
//		else if(((j!=-1)&&(i!=-1)))
//		{
//			if(j>7-i)
//				error_hou=eh[i]+eh[i-1];
//			else if(j==7-i)
//				error_hou=0;
//			else
//				error_hou=eh[j]+eh[j+1];
//		}
//		else
//			error_hou=0;
//		i=-1;
//		j=-1;
//	}
	
	
	
	if(((error_qian*error_hou)<0))
		error_all=(float)1.3*error_qian-(float)0.4*error_hou;//1.3
	
	
	
	if((error_qian*error_hou)>=0)
		error_all=(float)1.3*error_qian+(float)0.4*error_hou;




}

void xunji_high_speed(unsigned int speed){
	gethdnum();
	if(huidu_qian_num==0)      //**********
	{
		forward();
		TIM_SetCompare3(TIM3,60);
		TIM_SetCompare4(TIM3,70);
	}
	else
	{
		error();
		if(speed<300)
		{
			if(error_all>=(float)-1.5 && error_all<=(float)1.5)      ///speed 120
				PID_Init(&xunji_PID,9,0.02,200);
			else
				PID_Init(&xunji_PID,7,0,35);//4.2  0.08 90
		}
		if(speed>300)
		{
			if(error_all>=(float)-1.5 && error_all<=(float)1.5)      ///speed 120
				PID_Init(&xunji_PID,14,0,240);
			else
				PID_Init(&xunji_PID,5.5,0,45);//4.2  0.08 90			
		}
		out=PID_calc(&xunji_PID,error_all);
		out_left=speed+out;
		out_right=speed-out;
		out_right=out_right*((float)0.0005*(speed-200)+(float)1.075);//*(float)1.15;
		if(out_left<0)out_left=0;
		if(out_right<0)out_right=0;
		if(out_left>2*speed)out_left=2*speed;
		if(out_right>2*speed)out_right=2*speed;
		forward();
		TIM_SetCompare3(TIM3,out_right);
		TIM_SetCompare4(TIM3,out_left*1.2);
	}
}
void xunji(unsigned int speed){
	gethdnum();
	if(huidu_qian_num==0)      //**********
	{
		forward();
		TIM_SetCompare3(TIM3,60);
		TIM_SetCompare4(TIM3,70);
	}
	else
	{
	
		error();
	if(speed>=100)
	{
		if(error_all>=(float)-1.5 && error_all<=(float)1.5)      ///speed 120
			PID_Init(&xunji_PID,6,0,80);
		else
			PID_Init(&xunji_PID,5,0,60);//4.2  0.08 90  //5,0,50
	}
	
	if(speed<=100)
	{
		if(nowpingtai==6)
		{
			if(error_all>=(float)-1.5 && error_all<=(float)1.5)       ///speed 50
				PID_Init(&xunji_PID,8.9,0.8,70);
			else
				PID_Init(&xunji_PID,9.8,0.09,50);
		}
		else
		{
			if(error_all>=(float)-1.5 && error_all<=(float)1.5)       ///speed 50
				PID_Init(&xunji_PID,7.8,0.06,78);
			else
				PID_Init(&xunji_PID,8.9,0.12,50);
		}			
	}
		out=PID_calc(&xunji_PID,error_all);
		
		out_left=speed*1.1+out;
		out_right=(speed-out);
		if(out_left<0)out_left=0;
		if(out_right<0)out_right=0;
		if(out_left>2*speed)out_left=2*speed;
		if(out_right>2*speed)out_right=2*speed;
		forward();
		TIM_SetCompare3(TIM3,out_right);
		TIM_SetCompare4(TIM3,out_left+10);
	}
}

int get_now_yaw(){
	int angle_z;
	angle_z=angle[2];
	return angle_z;
}
void mpu_go_straight(int yaw_set){
	error_yaw=angle[2]-yaw_set;
	out=pid(1.5,0,10,error_yaw);
	out_left=75-out;
	out_right=75+out;
	if(out_left<0)out_left=0;
	if(out_right<0)out_right=0;
	if(out_left>160)out_left=160;
	if(out_right>160)out_right=160;
	forward();
	if(nowpingtai==4){
		TIM_SetCompare3(TIM3,out_right);
		TIM_SetCompare4(TIM3,out_left);
	}
	else{
		TIM_SetCompare3(TIM3,out_right);
		TIM_SetCompare4(TIM3,out_left+5);
	}
}

void huidu_go_straight2(){
	if(hwleft==0)
		out=13;
	else
		out=-5;
	out_left=65+out;
	out_right=65-out;

	forward();
	TIM_SetCompare3(TIM3,out_right);
	TIM_SetCompare4(TIM3,out_left);
}


void xunji_Init(u8 mode,u8 xj_gear){
	xunji_flag=mode;
	xunji_gear=xj_gear;

}
void xunji_ing(u8 mode1){
	switch(mode1)
	{
		case 0: break; 	//不执行操作 用于转弯
		
		case 1:xunji(80);break;
		
		case 2:xunji(65);break;  //用于转弯前
		
		case 100:goforward(xunji_gear);break;//盲走
		
		case 4://专门用于高平台下坡
			if(angle[1]>10&&angle[1]<50)xunji(20);
			else if(angle[1]<=10)xunji(35);
			else if(angle[1]>=50)xunji(35);
			break;
					
		case 9:
			if(xunji_gear==2)xunji_high_speed(360);	
			if(xunji_gear==1)xunji_high_speed(250);	
			break; //高速
			
		case 10:stop();break;
		
		case 50:mpu_go_straight(xunji_gear);break;
		
		case 11:colorcode_go_straight(xunji_gear);break;  // 色标循迹，用于长桥和跷跷板
		
		
		case 99:xunji(xunji_gear);break;

	}
}

// 左转（右轮独转）
void left_single2(int speed){
	DIR1=0;
	DIR2=1;//y
	
	DIR3=1;
	DIR4=0;
	TIM_SetCompare3(TIM3,speed);//you
	TIM_SetCompare4(TIM3,0);//1.1
}
// 右转（左轮独转）
void right_single2(int speed){
	DIR1=1;
	DIR2=0;//y
	
	DIR3=0;
	DIR4=1;
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,speed);
}


// 色标循迹           
void colorcode_go_straight(int speed){
	out=0;
	if(SBL==0)out=speed/2*3;
	else if(SBR==0)out=-speed/2*3; 
	
	out_left=speed+out;
	out_right=speed-out;
	forward();
	if(nowpingtai==6){
		TIM_SetCompare3(TIM3,out_right+20);   
		TIM_SetCompare4(TIM3,out_left);
	}else{
		TIM_SetCompare3(TIM3,out_right);
		TIM_SetCompare4(TIM3,out_left+15);
	}
}