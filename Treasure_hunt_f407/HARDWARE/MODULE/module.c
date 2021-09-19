#include "module.h"
#include "pid.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "trailing.h"
#include "logic.h"

step_struct constep={0,0,0,0,0,0,0,0,0,0,0,0};

int turn_little_angle_mark;
int turn_90_mark;
int flag=0;
int delaytime;
u8 nowpingtai=0;
int delaytime2;
u8 speed_step=0;
u8 time=0;
u8 time2=0;
u8 picture=0;
int all_delaytime=10,all_delaytime1=20;
int jiaoducha=0;
int Step = 0;
int treasure=2;
int kaca;
int shakehead_flag=0;



int mydelay(int time)
{
		delaytime++;
		if(delaytime>=time)
			return 1;
		else
			return 0;
}

void time_reset()
{
	time=0;
	delaytime=0;
}


int mydelay2(int time)
{
		delaytime2++;
		if(delaytime2>=time)
			return 1;
		else
			return 0;
				
}

void time_reset2()
{
	time2=0;
	delaytime2=0;
}






void high_speed(int low_speed_time,int high_speed_time,u8 gear)
 {
	switch(speed_step)
	{
		case 0:
			xunji_Init(99,65);
			time=mydelay(low_speed_time);//高速延时 跑的路程
			if(time==1)
			{
				time_reset();                          //************
				speed_step++;
			}		
			break;
		
		case 1:				//低速
			if(gear==2)
				xunji_start(360);
			if(gear==1)
				xunji_start(250);
			break;
			
		case 2:
			xunji_Init(9,gear);
			time=mydelay(high_speed_time);//高速延时 跑的路程
			if(time==1)
			{
				time_reset();                          //************
				speed_step++;
			}			
			break;
		
		case 3:
			stop_snub(100,'h');//速度切换延时
			break;
		
		case 4:
			xunji_Init(1,0);
			speed_step=0;
			step++;
			break;
	}
}



// 小角度转弯     
// 参数：                    方向
void turn_small_angle(char direction){
	switch(constep.turn_small_step){
			case 0:
					if(hd_qian[7]==0&&hd_qian[6]!=0&&hd_qian[5]!=0&&direction=='r'){xunji_Init(0,0);constep.turn_small_step=1;}
					else if(hd_qian[0]==0&&hd_qian[1]!=0&&hd_qian[2]!=0&&direction=='l'){xunji_Init(0,0);constep.turn_small_step=2;}
					break;
			// 右转		
			case 1:
					right(100);
					if(hd_qian[3]+hd_qian[4]==2)constep.turn_small_step=3;
					break;
			
			case 3:
					right(100);
					if(hd_qian[3]+hd_qian[4]<=1){xunji_Init(10,0);constep.turn_small_step=5;}
					break;
			// 左转		
			case 2:
					left(100);
					if(hd_qian[3]+hd_qian[4]==2)constep.turn_small_step=4;
					break;
			
			case 4:
					left(100);
					if(hd_qian[3]+hd_qian[4]<=1){xunji_Init(10,0);constep.turn_small_step=5;}
					break;
					
			case 5:break;
		}
	if(flag==0&&constep.turn_small_step==5){
		flag=1;
		constep.turn_small_step=0;
	}
}	
// 回家的小角度转弯
void turn_small_angle2(){
	gethdnum();
	switch(constep.turn_small_step){
		case 0:
				if(hd_qian[0]==0&&hd_qian[3]+hd_qian[4]<=1&&hd_qian[1]==1){xunji_Init(100,50);constep.turn_small_step++;}
				break;
		case 1:	if(hd_qian[3]+hd_qian[4]==2&&hd_qian[7]==0){xunji_Init(100,50);constep.turn_small_step++;}
		case 2:
				right(100);
				if(hd_qian[3]+hd_qian[4]==0){xunji_Init(10,0);constep.turn_small_step++;}
				break;
				
		case 3:break;
	}
	if(flag==0&&constep.turn_small_step==3){
		flag=1;
		constep.turn_small_step=0;
	}
}

	
	
// 九十度转弯   
// 参数：           方向         模式

void turn_90(char direction, int mode){
	
	//T型路口
	if(mode==1){
		switch(constep.turn_90_step){
			case 0:
					if(hd_qian[0]==0&&direction=='l'){xunji_Init(99,45);constep.turn_90_step++;}
					else if(hd_qian[7]==0&&direction=='r'){xunji_Init(99,45);constep.turn_90_step++;}
					break;
			case 1:if(HDL==0||HDR==0){xunji_Init(10,0);constep.turn_90_step++;}break;	
			case 2:time=mydelay(20);if(time==1){time_reset();constep.turn_90_step++;}break;
			case 3:
					if(direction=='l'){xunji_Init(0,0);constep.turn_90_step++;}
					else if(direction=='r'){xunji_Init(0,0);constep.turn_90_step++;}
					break;
					
			case 4:
					if(direction=='l')left(120);
					else if(direction=='r')right(120);
					if(hd_qian[3]+hd_qian[4]==2)constep.turn_90_step++;
					break;
			
			case 5:
					if(direction=='l')left(120);
					else if(direction=='r')right(120);
					if(hd_qian[3]+hd_qian[4]<=1)
						{xunji_Init(99,50);constep.turn_90_step++;}
					break;
						
			case 6:
					if(IsStright())constep.turn_90_step++;
					break;
			
			case 7:break;
		}
		if(flag==0&&constep.turn_90_step==7){
			flag=1;
			constep.turn_90_step=0;
		}
	}
		// 模式2  十字型路口
		if(mode==2){
			
			switch(constep.turn_90_step){
				
				case 0:
						if(hd_qian[0]+hd_qian[7]==0)
							{xunji_Init(99,50);constep.turn_90_step++;}
						break;

				case 1:
						if(HDL==0&&direction=='l'){xunji_Init(0,0);constep.turn_90_step++;}
						else if(HDR==0&&direction=='r'){xunji_Init(0,0);constep.turn_90_step++;}
						break;
				
				case 2:
						if(direction=='l')left(120);else if(direction=='r')right(120);
						if(hd_qian[3]+hd_qian[4]==2)constep.turn_90_step++;
						break;
				
				case 3:
						if(direction=='l')left(120);else if(direction=='r')right(120);
						if(hd_qian[3]+hd_qian[4]<=1){xunji_Init(99,65);constep.turn_90_step++;}
						break;
				
				case 4:
						if(hd_qian[3]+hd_qian[4]<=1&&hd_hou[3]+hd_hou[4]<=1)constep.turn_90_step++;
						break;
				
				case 5:break;
			}
		if(flag==0&&constep.turn_90_step==5){
			flag=1;
			constep.turn_90_step=0;
		}
	}
		// 模式3  需要转两根线
		if(mode==3){
			
			switch(constep.turn_90_step){
				
				case 0:
						if(hd_qian[3]+hd_qian[4]+hd_qian[0]==0&&hd_qian[1]==1&&direction=='l'){xunji_Init(0,0);constep.turn_90_step++;}
						else if(hd_qian[3]+hd_qian[4]+hd_qian[7]==0&&hd_qian[6]==1&&direction=='r'){xunji_Init(0,0);constep.turn_90_step++;}
						break;
				
				case 1:
							if(direction=='l')left(120);
							else if(direction=='r')right(120);
							if(hd_qian[3]+hd_qian[4]==2)constep.turn_90_step++;
							break;
					
					case 2:
							if(direction=='l')left(120);
							else if(direction=='r')right(120);
							if(hd_qian[3]+hd_qian[4]<=1)constep.turn_90_step++;
							break;
					
					case 3:
							if(direction=='l')left(120);
							else if(direction=='r')right(120);
							if(hd_qian[3]+hd_qian[4]==2)constep.turn_90_step++;
							break;
					
					case 4:
							if(direction=='l')left(120);
							else if(direction=='r')right(120);
							if(hd_qian[3]+hd_qian[4]<=1)constep.turn_90_step++;
							break;
					case 5:
							xunji_Init(99,65);
							if(hd_qian[3]+hd_qian[4]<=10&&hd_hou[3]+hd_hou[4]==0)constep.turn_90_step++;
							break;
					
					case 6:
							xunji_Init(99,65);
							break;
			}
		if(flag==0&&constep.turn_90_step==6){
			flag=1;
			constep.turn_90_step=0;
		}
	}
}
			

	
	

// 上平台转180度
void platform(int z_angle){
	// 上高平台
	if(nowpingtai==7||nowpingtai==8){
		switch(constep.platform_step){
			
			case 0:
					if(gd2==0)constep.platform_step=4;
					else{
					//if(angle[1]>10&&angle[1]<350)xunji_Init(99,120);
					if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]==8&&angle[1]>10&&angle[1]<50)
					{xunji_Init(99,100);
						
					if(nowpingtai==8&&(angle[1]<10||angle[1]>50))constep.platform_step=1;
					else if(nowpingtai==7)constep.platform_step=2;}}
					break;
			case 1:
					if(gd2==0)constep.platform_step=4;
					else{
					if(angle[1]>10&&angle[1]<350)xunji_Init(99,120);
					if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]==8&&angle[1]>10&&angle[1]<350)
					{xunji_Init(99,100);constep.platform_step++;}}
					break;
			
			case 2:
					if(gd2==0)constep.platform_step=4;
					else{
					time=mydelay(50);
					if(time==1){time_reset();xunji_Init(100,90);constep.platform_step++;}}
					break;
			case 3:
					if(gd2==0)constep.platform_step=4;
					else{
					if(angle[1]>=350 && (HDR==0 && HDL==0)){xunji_Init(99,30);constep.platform_step++;}
					else if(angle[1]<=10 && (HDR==0 && HDL==0)){xunji_Init(99,30);constep.platform_step++;}}
					break;
			
			case 4:
					xunji_Init(0,0);constep.platform_step++;
					break;
					
			case 5:
							jiaoducha=angle[2]-z_angle;
						if(jiaoducha>=0)jiaoducha=jiaoducha;
						else jiaoducha=360+angle[2]-z_angle;
						if(jiaoducha<=55)left(200);
				    else left(100);
						if(jiaoducha>=175&&jiaoducha<=190){stop();jiaoducha=0;constep.platform_step++;}
						break;								
			case 6:xunji_Init(10,0);break;
			}
		if(flag==0&&constep.platform_step==6){
			flag=1;
			constep.platform_step=0;
		}
	}
	else if(nowpingtai==1){
		switch(constep.platform_step){
			
			case 0:
					if(GD2==0)constep.platform_step=4;
					//if(angle[1]>10&&angle[1]<50)xunji_Init(99,120);
					if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]==8&&angle[1]>10&&angle[1]<50)
					{xunji_Init(100,100);constep.platform_step++;}
					break;
			
			case 1:
					if(GD2==0)constep.platform_step=4;
					time=mydelay(50);
					if(time==1){time_reset();xunji_Init(100,50);constep.platform_step++;}break;
			case 2:
					if(GD2==0)constep.platform_step=4;
					if(angle[1]>=50 && (HDR==0 && HDL==0)){xunji_Init(99,30);constep.platform_step++;}
					else if(angle[1]<=10 && (HDR==0 && HDL==0)){xunji_Init(99,30);constep.platform_step++;}
					break;
			
			case 3:

					if(angle[1]>=350 && (HDR==1 && HDL==1)){xunji_Init(0,0);constep.platform_step++;}
					else if(angle[1]<=5 && (HDR==1 && HDL==1)){xunji_Init(0,0);constep.platform_step++;}
					break;
					
			case 4:xunji_Init(10,0);time=mydelay(100);if(time==1){time_reset();xunji_Init(0,0);constep.platform_step++;}break;	
			case 5:
							jiaoducha=angle[2]-z_angle;
						if(jiaoducha>=0)jiaoducha=jiaoducha;
						else jiaoducha=360+angle[2]-z_angle;
						if(jiaoducha<=55)left(200);
				    else left(100);
						if(jiaoducha>=175&&jiaoducha<=190){stop();jiaoducha=0;constep.platform_step++;}
						break;
			case 6:break;
					}
		if(flag==0&&constep.platform_step==6){
			flag=1;
			constep.platform_step=0;}
				}
	// 普通平台
	else {
		switch(constep.platform_step){
			
			case 0:get_now_hd();
					if(gd2==0)constep.platform_step=3;
					else{
					//if(angle[1]>5&&angle[1]<350)xunji_Init(99,120);
					if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]>=5&&angle[1]>5&&angle[1]<350)
					{xunji_Init(100,100);constep.platform_step++;}
				}
					break;
			
			case 1:get_now_hd();
					if(gd2==0)constep.platform_step=3;
			else{
					time=mydelay(50);
					if(time==1){time_reset();xunji_Init(100,90);constep.platform_step++;}
				}break;
			case 2:
					
					if((angle[1]>=355 && (HDR==0 && HDL==0))||gd2==0){xunji_Init(10,0);constep.platform_step++;}
					else if((angle[1]<=5 && (HDR==0 && HDL==0))||gd2==0){xunji_Init(10,0);constep.platform_step++;}
					break;
//			case 0:if(angle[1]<=355&&angle[1]>=10){xunji_Init(100,90);constep.platform_step++;}break;
//			case 1:time=mydelay(100);if(time==1){time_reset();xunji_Init(10,0);constep.platform_step=3;}break;
//			case 0:if(GD2==0){xunji_Init(10,0);constep.platform_step=3;}break;
			case 3:time=mydelay(50);if(time==1){time_reset();
					xunji_Init(10,0);kaca=0;shakehead_flag=0;constep.platform_step++;}
					break;
					
			case 4:xunji_Init(10,0);
						if(nowpingtai==2){
									if(shakehead_flag==0)ShakeHead();
									else if(shakehead_flag==1){
											if(kaca==0)GetTreasure();
											else if(kaca==1) {xunji_Init(0,0);constep.platform_step=6;}}
										}
							else constep.platform_step++;	break;
							
			case 5:	if(((nowpingtai==image[0]||image[0]==0)&&(nowpingtai==3||nowpingtai==4))||
								((nowpingtai==image[1]||image[1]==0)&&(nowpingtai==5||nowpingtai==6))||nowpingtai==2){
								if(kaca==0)GetTreasure();
								else {xunji_Init(0,0);constep.platform_step++;}}
						 else {xunji_Init(0,0);constep.platform_step++;}break;
			case 6:
							jiaoducha=angle[2]-z_angle;
						if(jiaoducha>=0)jiaoducha=jiaoducha;
						else jiaoducha=360+angle[2]-z_angle;
						if(jiaoducha<=55)left(200);
				    else left(100);
						if(jiaoducha>=175&&jiaoducha<=190){stop();jiaoducha=0;constep.platform_step++;}
						break;
				
			case 7:xunji_Init(10,0);break;
			}
		if(flag==0&&constep.platform_step==7){
			flag=1;
			constep.platform_step=0;
		}
	}
//if(flag==0){xunji_Init(10,0);time=mydelay(400);
//	   if(time==1){
//			 time_reset();
//			flag=1;
//			constep.platform_step=0;
//		}
//	}
}



// 长桥
void bridge(){

	gethdnum();
	
	switch(constep.bridge_step){
		case 0:
				if(angle[1]>20 &&angle[1]<55 )xunji_Init(100,90);
				if(hd_hou[3]+hd_hou[4]+hd_hou[2]+hd_hou[1]+hd_hou[0]+hd_hou[5]+hd_hou[6]+hd_hou[7]==8
					&& hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+hd_qian[5]+hd_qian[6]+hd_qian[7]==8 
					&& (angle[1]<=5||angle[1]>=50))constep.bridge_step++;
				break;
				
		case 1:
				xunji_Init(11,100);
				time=mydelay(50);//高速延时 跑的路程
				if(time==1){time_reset();constep.bridge_step++;}			
				break;
				
		case 2:
				xunji_Init(11,50);
				if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]<8)constep.bridge_step++;
				break;
		
		case 3:
				xunji_Init(99,50);
				if(hd_qian[3]+hd_qian[4]<=1 &&hd_hou[3]+hd_hou[4]<=1)constep.bridge_step++;
				break;
		
		case 4:break;
			
	}
			
		if(flag==0&&constep.bridge_step==4){
			flag = 1;
			constep.bridge_step = 0;
		}
		
}








// 跷跷板
// 参数：mode 1为普通  2为跑圆	
void seesaw(int mode){ 
	if(mode==1){
	switch(constep.seesaw_step){
		
		case 0:
				if(hd_qian[3]+hd_qian[4]+hd_qian[5]+hd_qian[2]+hd_qian[0]+hd_qian[1]+hd_qian[6]+hd_qian[7]==8){xunji_Init(0,0);constep.seesaw_step=1;}
				break;
		
		case 1:
				left_single2(80);
				time=mydelay(30);
				if(time==1){time_reset();xunji_Init(11,90);constep.seesaw_step=2;}	
				break;
		
		case 2:
				if(hd_qian[3]+hd_qian[4]+hd_qian[5]+hd_qian[2]==4&&hd_hou[2]+hd_hou[3]+hd_hou[4]+hd_hou[5]==4&&angle[1]>5&&angle[1]<55){xunji_Init(11,65);constep.seesaw_step=3;}
				break;
		
    case 3:
				if(angle[1]<5){xunji_Init(0,0);constep.seesaw_step=3;}else if(angle[1]>55){xunji_Init(0,0);constep.seesaw_step=4;}
				break;
				
		case 4:
				left_single2(80);
				if(hd_qian[3]+hd_qian[4]+hd_qian[5]+hd_qian[6]+hd_qian[7]<5){nowpingtai=6;xunji_Init(99,45);constep.seesaw_step=5;}
				break;
				
		case 5:break;
	}	
		if(flag==0&&constep.seesaw_step==5){
				flag=1;
				constep.seesaw_step=0;
			}
		}
	else if(mode==2){
			switch(constep.seesaw_step){
		
		case 0:
				if(hd_qian[3]+hd_qian[4]+hd_qian[5]+hd_qian[2]+hd_qian[0]+hd_qian[1]+hd_qian[6]+hd_qian[7]==8){xunji_Init(11,120);constep.seesaw_step++;}
				break;
		
		
		case 1:
				time=mydelay(200);if(time==1){xunji_Init(10,0);constep.seesaw_step++;time_reset();}break;
		
		case 2:
				time=mydelay(50);if(time==1){xunji_Init(99,40);constep.seesaw_step++;time_reset();}break;
				
		case 3:		
				if(hd_qian[3]+hd_qian[4]<=1){xunji_Init(99,45);constep.seesaw_step++;}
				break;
				
		case 4:break;
	}	
		if(flag==0&&constep.seesaw_step==4){
				flag=1;
				constep.seesaw_step=0;
			}
		}
}

	



// 转弯
// 参数：        方向          模式
void turn(char direction, int mode){
		
	
	// 模式1  由平台三到五或四到六的五岔路口转弯
	if(mode==1){
			switch(constep.turn_step){
					
					case 0:
							if(hd_qian[7]==0){xunji_Init(99,65);constep.turn_step++;}
							break;
							
					case 1:
							if(hd_qian[0]==0&&hd_qian[3]+hd_qian[4]==2){xunji_Init(0,0);constep.turn_step++;}
							break;
							
					case 2:
							if(direction=='l')left(120);else if(direction=='r')right(120);
							if(hd_qian[3]+hd_qian[4]<=1){xunji_Init(10,0);constep.turn_step++;}
							break;
							
					case 3:break;
			}
			if(flag==0&&constep.turn_step==3){
				flag=1;
				constep.turn_step=0;
			}
		}
		
		
	
		
	// 模式2  跑圆上跷跷板的转弯
	if(mode==2){
			switch(constep.turn_step){
					
					case 0:
							if(hd_qian[7]==0&&hd_qian[0]==1){xunji_Init(0,0);constep.turn_step=1;}
							break;
					
					case 1:
							right(120);
							if(hd_qian[3]+hd_qian[4]==2)constep.turn_step=2;
							break;
					
					case 2:
							right(120);
							if(hd_qian[3]+hd_qian[4]<=1)constep.turn_step=3;
							break;
					
					case 3:
							right(120);
							if(hd_qian[3]+hd_qian[4]==2)constep.turn_step=4;
							break;
					
					case 4:
							right(120);
							if(hd_qian[3]+hd_qian[4]<=1&&hd_hou[3]+hd_hou[4]==2)constep.turn_step=5;
							break;
					
					case 5:
							xunji_Init(99,65);
							break;
			}
			if(flag==0&&constep.turn_step==5 ){
				flag=1;
				constep.turn_step=0;
			}
		}
		
		
	// 模式3  圆上的转弯
	if(mode==3){
			switch(constep.turn_step){
				case 0:
						if(hd_qian[3]+hd_qian[4]+hd_qian[5]+hd_qian[2]+hd_qian[0]+hd_qian[1]+hd_qian[6]+hd_qian[7]==8&&hd_hou[3]+hd_hou[4]<=1)
							{xunji_Init(99,45);constep.turn_step++;}
						break;
				case 1:time=mydelay(20);if(time==1){time_reset();constep.turn_step++;}break;
				case 2:xunji_Init(0,0);constep.turn_step++;
						break;
				
				case 3:
						left(120);
						if(hd_qian[0]==0)constep.turn_step++;
						break;
				
				case 4:
						left(120);
						if(hd_qian[4]+hd_qian[5]<=1)constep.turn_step++;
						break;
				
				case 5:break;
			}
			if(flag==0&&constep.turn_step==5 ){
				flag=1;
				constep.turn_step=0;
			}
	}
}
	




// 斜面
// 参数：     模式
void slop(int mode){
	
	// 模式1  平台2到4的斜面
	if(mode==1){
		switch(constep.slop_step){
			
			case 0:
					if(SBR==0 && hd_hou[3]+hd_hou[4]+hd_hou[5]==3){xunji_Init(0,0);constep.slop_step++;}
					break;
					
			case 1:
					left_single2(100);
					time=mydelay(40);if(time==1){time_reset();constep.slop_step++;}
					break;
			
			case 2:
					xunji_Init(100,80);
					gethdnum();
					if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]<8){xunji_Init(99,60);constep.slop_step++;}
					break;
					
			case 3:
					if(hd_qian[3]+hd_qian[4]<=1&&hd_hou[3]+hd_hou[4]<=1)constep.slop_step++;
					break;
			
			case 4:break;
		}
		if(constep.slop_step==4&&flag==0){
			constep.slop_step=0;
			flag=1;
		}
	}
	
	
	
	// 模式2  直走斜面
		if(mode==2){
		switch(constep.slop_step){
			case 0:
				xunji_Init(99,65);
				now_yaw=angle[2];
				constep.slop_step++;				 						
				break;
			case 1:
				if(hd_qian[3]==1&&hd_qian[4]==1){
				xunji_Init(50,now_yaw);constep.slop_step++;}
				break;
			case 2:nowpingtai=4;
							if(angle[1]>6 && angle[1]<350)xunji_Init(50,now_yaw);
							time=mydelay(100);if(time==1){time_reset();constep.slop_step++;}
							break;
			case 3:if(angle[1]<6||angle[1]>350)nowpingtai=0;
				if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]<8){xunji_Init(99,65);constep.slop_step++;}
					else xunji_Init(50,now_yaw);
			break;
			case 4:
				if(hd_qian[3]+hd_qian[4]<=1 && hd_hou[3]+hd_hou[4]<=1)constep.slop_step++;
				break;
			case 5:break;
		}
		if(constep.slop_step==5&&flag==0){
			constep.slop_step=0;
			flag=1;
		}
	}
	
	
	
	// 模式3  斜面右转90度
	if(mode==3){
		switch(constep.slop_step){
			case 0:
					if(hd_qian[3]+hd_qian[4]+hd_qian[2]+hd_qian[5]==4){xunji_Init(100,65);constep.slop_step++;}
					break;
					
			case 1:
					if(SBL+SBR==0){xunji_Init(0,0);constep.slop_step++;}
					break;
					
			case 2:
					right(80);
					time=mydelay(100);if(time==1){time_reset();constep.slop_step++;}
					break;
					
			case 3:
					xunji_Init(11,65);
					if(hd_qian[3]+hd_qian[4]==0){constep.slop_step++;xunji_Init(99,20);}
					break;
					
			case 4:break;
		}
		if(constep.slop_step==4&&flag==0){
			constep.slop_step=0;
			flag=1;
		}
	}
	
	
	
	// 模式4  斜面左转90度
	if(mode==4){
		switch(constep.slop_step){
			case 0:
					if(hd_qian[3]+hd_qian[4]+hd_qian[2]+hd_qian[5]==4){xunji_Init(100,65);constep.slop_step++;}
					break;
					
			case 1:
					if(SBL+SBR==0){xunji_Init(0,0);constep.slop_step++;}
					break;
					
			case 2:
					left(80);
					time=mydelay(100);if(time==1){time_reset();constep.slop_step++;}
					break;
					
			case 3:
					if(angle[1]>5&&angle[1]<355)xunji_Init(11,65);
					else if(angle[1]<5||angle[1]>355)xunji_Init(100,50);
					if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
					hd_qian[5]+hd_qian[6]+hd_qian[7]<8){constep.slop_step++;xunji_Init(99,65);}
					break;
					
			case 4:break;
		}
		if(constep.slop_step==4&&flag==0){
			constep.slop_step=0;
			flag=1;
		}
	}
	
////	// 模式5 平台2到平台3的斜面
////	if(mode==5){
////				switch(constep.slop_step){
////					case 0:
////							gethdnum();
////							if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
////									hd_qian[5]+hd_qian[6]+hd_qian[7]==8){xunji_Init(11,65);
////									delay_ms(50);xunji_Init(0,0);constep.slop_step++;}
////							break;
////					case 1:
////							left_single2(80);
////							
////							if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+
////						hd_qian[5]+hd_qian[6]+hd_qian[7]<8){xunji_Init(99,60);constep.slop_step++;}
////							break;
////					
////					case 2:
////							if(hd_qian[3]+hd_qian[4]<=1&&hd_hou[3]+hd_hou[4]<=1)constep.slop_step++;
////							break;
////			
////					case 3:break;
////		}
////		if(constep.slop_step==3&&flag==0){
////			constep.slop_step=0;
////			flag=1;
////		}
////	}
////	
	// 模式5 回家的斜面1 靠近平台7&8的斜面
	if(mode==5){
				switch(constep.slop_step){
					case 0:if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]+hd_qian[4]+hd_qian[6]+hd_qian[7]+hd_qian[5]==8)constep.slop_step++;break;
					
					case 1:xunji_Init(100,80);
								now_yaw=angle[0];
								constep.slop_step++;
								break;
					
					case 2:if(((angle[0]-now_yaw>3)||(angle[0]-now_yaw<-3))&&angle[1]>3&&angle[1]<50)
									constep.slop_step++;
									break;
					
					case 3:	time=mydelay(100);
								if(time==1){time_reset();xunji_Init(10,0);constep.slop_step++;}
							break;
			
					case 4:xunji_Init(0,0);
								left_single2(100);time=mydelay(75);
								if(time==1||(hd_qian[0]==0)){time_reset();constep.slop_step++;}
							break;
									
					case 5:left(80);if(hd_qian[3]+hd_qian[4]<=1){xunji_Init(99,50);constep.slop_step++;}break;
									
					case 6:if(hd_qian[3]+hd_qian[4]<=1&&hd_hou[3]+hd_hou[4]<=1){
								xunji_Init(99,65);constep.slop_step++;}
							break;
					case 7:break;
						
		}
		if(constep.slop_step==7&&flag==0){
			constep.slop_step=0;
			flag=1;
		}
	}
	
	// 模式6 回家的斜面2 靠近平台1的斜面
	if(mode==6){ 
		switch(constep.slop_step){
			case 0:
				if(hd_qian[3]==1&&hd_qian[4]==1){constep.slop_step++;}		 						
				break;
				
			case 1:xunji_Init(100,80);
								now_yaw=angle[0];
								constep.slop_step++;
								break;
					
			case 2:if(((angle[0]-now_yaw>3)||(angle[0]-now_yaw<-3))&&angle[1]>3&&angle[1]<50)
								constep.slop_step++;
								break;
					
			case 3:	time=mydelay(150);
							if(time==1){time_reset();xunji_Init(10,0);constep.slop_step++;}
							break;
			
			case 4:xunji_Init(0,0);
						left_single2(100);time=mydelay(75);
							if(time==1||(hd_qian[0]+hd_qian[01]+hd_qian[2]+hd_qian[3]+hd_qian[4]
										+hd_qian[5]+hd_qian[6]+hd_qian[7]<8)){time_reset();constep.slop_step++;}
							break;
									
			case 5:xunji_Init(99,40);if(hd_qian[3]+hd_qian[4]<=1){xunji_Init(99,45);constep.slop_step++;}break;
									
			case 6:if(hd_qian[3]+hd_qian[4]<=1&&hd_hou[3]+hd_hou[4]<=1){
							xunji_Init(99,65);constep.slop_step++;}
							break;
			case 7:break;
		}
		if(constep.slop_step==7&&flag==0){
			constep.slop_step=0;
			flag=1;
		}
	}
}





// 减速带
void decestrip(){
	switch(constep.decestrip_step){
		case 0:
				xunji_Init(99,65);
				if(SBR==0||SBL==0)constep.decestrip_step++;
				break;
		
		case 1:
				xunji_Init(99,65);
				time=mydelay(400);if(time==1){time_reset();constep.decestrip_step++;}
				break;
				
		case 2:
				xunji_Init(99,60);
				break;
	}
	if(flag==0&&constep.decestrip_step==2){
		flag=1;
		constep.decestrip_step=0;
	}
}
	



// 门
void doors(){
	switch(constep.door_step){
		
		
		case 0:time=mydelay(150);if(time==1){time_reset();constep.door_step++;}break;
		case 1:if(HDL==0||HDR==0)constep.door_step++;break;
		case 2:time=mydelay(150);if(time==1){time_reset();constep.door_step++;}break;
		case 3:break;
				
	}
		if(flag==0&&constep.door_step==3){
		flag=1;
		constep.door_step=0;
	}
}
	
void go_down_platform(){
	switch(constep.go_down_platform){
		case 0:	xunji_Init(100,50);constep.go_down_platform++;break;
		case 1:time=mydelay(50);if(time==1){time_reset();xunji_Init(99,50);constep.go_down_platform++;}break;
		case 2:if(hd_qian[3]+hd_qian[4]<=1&&hd_hou[0]+hd_hou[7]==2&&
					hd_hou[3]+hd_hou[4]<=1&&hd_qian[0]+hd_qian[7]==2&&HDL+HDR==2)constep.go_down_platform++;break;
		case 3:break;
	}     
		if(constep.go_down_platform==3&&flag==0){
			constep.go_down_platform=0;
			flag=1;
		}
		
}
int IsStright(){
	if(hd_qian[3]+hd_qian[4]==0&&hd_hou[3]+hd_hou[4]==0) return 1;
	else return 0;
}
void GetTreasure(){
	if(nowpingtai==2){
			if(image[0]!=3||image[0]!=4){time2=mydelay2(500);if(time2==1){
				USART_SendData(USART3, 0x6B);time_reset2();}
		time=mydelay(1500);if(time==1||(image[0]==3||image[0]==4)){time_reset();kaca=1;}}
	}
	if(nowpingtai==3||nowpingtai==4){
			if(image[1]!=5||image[1]!=6){time2=mydelay2(1000);if(time2==1){
				USART_SendData(USART3, 0x6B);time_reset2();}
		time=mydelay(3000);if(time==1||(image[1]==6||image[1]==5)){time_reset();kaca=1;}}
	}
	if(nowpingtai==5||nowpingtai==6)	{
			if(image[2]!=7||image[2]!=8){time2=mydelay2(1000);if(time2==1){
				USART_SendData(USART3, 0x6B);time_reset2();}
		time=mydelay(3000);if(time==1||(image[2]==6||image[2]==5)){time_reset();kaca=1;}}
	}
}

void ShakeHead(){
	switch(constep.shakehead_step){
		case 0:TIM_SetCompare2(TIM4,100);//头
						constep.shakehead_step++;break;
		case 1:time2=mydelay2(50);if(time2==1){time_reset2();constep.shakehead_step++;}
					break;
		case 2:TIM_SetCompare2(TIM4,50);//头
						constep.shakehead_step++;break;
		case 3:time2=mydelay2(50);if(time2==1){time_reset2();constep.shakehead_step++;}
					break;
		case 4:TIM_SetCompare2(TIM4,150);//头
						constep.shakehead_step++;break;
		case 5:time2=mydelay2(50);if(time2==1){time_reset2();constep.shakehead_step++;}
					break;
		case 6:TIM_SetCompare2(TIM4,50);//头
					constep.shakehead_step++;break;
		case 7:time2=mydelay2(50);if(time2==1){time_reset2();constep.shakehead_step++;}
					break;
		case 8:break;
	}
	if(constep.shakehead_step==8&&flag==0){shakehead_flag=1;}
}
void ShakeHand(){
		switch(constep.shakehand_step){
			case 0://TIM_SetCompare4(TIM4,90);//左手
						//		TIM_SetCompare3(TIM4,45);//右手
								TIM_SetCompare4(TIM4,20);//左手
							constep.shakehand_step++;break;
			case 1:time2=mydelay2(60);if(time2==1){time_reset2();constep.shakehand_step++;}
							break;
			case 2:  // TIM_SetCompare3(TIM4,75);
								TIM_SetCompare3(TIM4,75);//右手
						//		TIM_SetCompare4(TIM4,90);//左手
							constep.shakehand_step++;break;
			case 3:time2=mydelay2(60);if(time2==1){time_reset2();constep.shakehand_step++;}
							break;
			case 4:	TIM_SetCompare3(TIM4,45);//右手
							TIM_SetCompare4(TIM4,115);//左手
							constep.shakehand_step++;break;
			case 5:time2=mydelay2(60);if(time2==1){time_reset2();constep.shakehand_step++;}
							break;
			case 6:break;
							}
		if(constep.shakehand_step==6&&flag==0){
			constep.shakehand_step=0;
			flag=1;
		}
	}



		