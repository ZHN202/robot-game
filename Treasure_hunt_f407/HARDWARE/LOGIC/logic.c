#include "logic.h"
#include "module.h"
#include "pid.h"
#include "trailing.h"
#include "led.h"
#include "delay.h"




/**************************************************************************//**
 * 				GOATOB    完成后会将step归零  Step加一
 * 
 * 				标** 代表还未完成
 * 				标*  代表需要完善
 *
 * 
 *
 ******************************************************************************/


int intersection;  // 路口值
u8 step=0;  // GOATOB中的步骤
u8 all_step=0;  // 遍历中的步骤
int start;




// 遍历所有平台**
void all(){
	switch(Step){
			case 0:
						GO1TO2();
						break;
			case 1:
						GO2TO4();
						break;
			case 2:
						GO4TO3();
						break;
			case 3:
						GO3TO5();
						break;
			case 4:
						GO5TO6();
						break;
			case 5:
						GO6TO7();
						break;
			case 6:
						GO7TO8();
						break;
			case 7:gohome8();break;
			
			case 8:break;
		
		}

}










// 寻宝遍历**
void all_only_three_treassure(){
	switch(all_step)
	{
		case 0:GO1TO2();break;
		
//		case 1:
//			if(image[0]==3)GO2TO3();
//			else if(image[0]==4)GO2TO4();
//			else xunji_Init(10,0);
//			break;
//		
//		case 2:
//			if(image[0]==3){   			if(image[1]==5)GO3TO5();  if(image[1]==6)GO3TO6();}
//			else if(image[0]==4){   if(image[1]==5)GO4TO5();  if(image[1]==6)GO4TO6();}
//			else xunji_Init(10,0);
//			break;
//		
//		case 3:
//			if(image[1]==5){   			if(image[2]==7)GO5TO7();  if(image[2]==8)GO5TO8();}
//			else if(image[1]==6){	  if(image[2]==7)GO6TO7();  if(image[2]==8)GO6TO8();}
//			else xunji_Init(10,0);
//			break;
//		
//		case 4:
//			if(image[2]==7)gohome7();
//			else if(image[2]==8)gohome8();
//			else xunji_Init(10,0);
//			break;
		
		case 5:
			xunji_Init(10,0);
			break;
	}
}









// 从平台1到平台2
void GO1TO2(){

	switch(step)
	{
		case 0:flag=0;
					go_down_platform();
					if(flag==1){xunji_Init(99,80);step++;}break;
		
		case 1:flag = 0;
		       bridge();	
		       if(flag == 1){now_yaw = angle[2];xunji_Init(99,80);step++;}
        	 break;
//		case 2:get_now_hd();if(gd2==0){xunji_Init(10,0);time=mydelay(50);if(time==1){time_reset();step=3;}}break;	
//		case 3:flag=0;
//						ShakeHead();
//					if(flag==1)step++;
//					break;
		case 2:flag = 0;nowpingtai=2;
					 platform(now_yaw);
	         if(flag == 1)step++;	
		       break;
		case 3:nowpingtai=0;stop();break;
	}
	if(step==3){
		step=0;
		Step++;
	}
}








// 从平台2到平台4*
void GO2TO4(){
	switch(step)
	{
		
		case 0:flag=0;
					go_down_platform();
					if(flag==1){xunji_Init(99,65);step++;}break;
		
		case 1: flag=0;
						turn_small_angle('r');
						if(flag==1)step++;
						break;
		
		case 2:	
						flag=0;
						decestrip();   
						if(flag==1){xunji_Init(99,50);step++;}
						break;
		
		case 3:	flag=0;
						slop(1);
						if(flag==1)step++;
						break;
		
		case 4:xunji_Init(99,65);if(IsStright())step++;break;
		case 5:	now_yaw = angle[2];high_speed(50,50,1);break;
					
		case 6:flag = 0;nowpingtai=4;
					 platform(now_yaw);
	         if(flag == 1)step++;	
		       break;
		case 7:flag=0;
						if((image[0]==4&&flag==0)||(image[0]==0&&image[1]==4&&flag==0))ShakeHand();
						if(flag == 1)step++;
						if(image[0]!=4&&image[0]!=0)step++;
						break;
		case 8:nowpingtai=0;stop();break;
	}
	if(step==8){
		step=0;
		Step++;
	}
}






//// 从平台2到平台3*        //斜面还未调试其他理论上可行
//void GO2TO3(){
//	switch(step)
//	{
//		case 0:if(go_down_platform()==1)step++;break;
//		
//		case 1:flag=0;
//						turn_small_angle('r');
//						if(flag==1)step++;
//						break;
//		
//		case 2:	xunji_Init(99,65);
//						flag=0;
//						decestrip();
//						if(flag==1)step++;
//						break;
//		
//		case 3:	flag=0;
//						slop(5);  // 未完成
//						if(flag==1)step++;
//						break;
//		case 4:xunji_Init(99,65);if(IsStright())step++;break;
//		case 5:	now_yaw = get_now_yaw();high_speed(50,120,1);break;
//					
//		case 6:flag = 0;
//					 platform(now_yaw);
//	         if(flag == 1)step++;	
//		       break;
//		case 7:stop();break;
//	}
//	if(step==7){
//		step=0;
//		Step++;
//	}
//}









// 从平台4到平台3*
void GO4TO3(){
	switch(step)
	{
		case 0:flag=0;
					go_down_platform();
					if(flag==1){xunji_Init(99,80);step++;}break;
		case 1:xunji_Init(10,0);
						time=mydelay(50);if(time==1){time_reset();step++;}break;
		case 2:high_speed(200,100,1);break;
		
		case 3:flag=0;
						slop(2);
						if(flag==1)step++;
						break;
		
		case 4:xunji_Init(99,65);if(IsStright())step++;break;
		case 5:now_yaw = angle[2];high_speed(50,50,1);break;	
		
		case 6:flag = 0;nowpingtai=3;
					 platform(now_yaw);
	         if(flag == 1)step++;	
		       break;
		
		case 7:flag=0;
						if((image[0]==3&&flag==0)||(image[0]==0&&flag==0&&image[1]==3))ShakeHand();
						if(flag == 1)step++;
						if(image[0]!=3&&image[0]!=0)step++;
						break;
		case 8:nowpingtai=0;stop();break;
			
	}
		if(step==8){
		step=0;
		Step++;
	}
}








// 从平台5到平台6*
void GO5TO6(){
	switch(step){
		case 0:flag=0;
					go_down_platform();
					if(flag==1){xunji_Init(99,80);step++;}break;
		case 1:xunji_Init(10,0);
						time=mydelay(50);if(time==1){time_reset();intersection=0;step++;}break;
		case 2:high_speed(100,200,1);//if(HDL==0&&HDR==0)intersection++;
						break;  
		case 3:high_speed(100,200,1);//if(HDL==0&&HDR==0)intersection++;
						break;  
		case 4:xunji_Init(99,65);//if(HDL==0&&HDR==0)intersection++;if(intersection>=2)
						step++;break;				
		
		case 5:
						flag = 0;
						turn('l',2);
						if(flag == 1)step++;	
						break;
		case 6:xunji_Init(99,60);nowpingtai=6;step++;break;
		case 7:
					 flag = 0;
					 seesaw(1);
	         if(flag == 1)step++;	
		       break;
		case 8:flag = 0;
					 turn_90('l',1);
	         if(flag == 1){now_yaw = angle[2];nowpingtai=0;step++;	}
		       break;
		case 9:flag = 0;nowpingtai=6;			
					 platform(now_yaw);
	         if(flag == 1)step++;	
		       break;
		
		case 10:flag=0;
						if(image[1]==6&&flag==0)ShakeHand();
						if(flag == 1)step++;
						if(image[1]!=6)step++;
						break;
		case 11:nowpingtai=0;stop();break;
	}
		if(step==11){
		step=0;
		Step++;
	}
}








// 从平台3到平台5*
void GO3TO5(){
	switch(step)
	{
		case 0:flag=0;
					go_down_platform();
					if(flag==1){xunji_Init(99,80);step++;}break;
		case 1:xunji_Init(10,0);
						time=mydelay(50);if(time==1){time_reset();step++;}break;
		case 2:	high_speed(200,50,1);break;
			
		case 3:flag=0;
						turn_small_angle('r');
						if(flag==1){xunji_Init(99,80);step++;}
						break;
		
		case 4:flag = 0;
					 doors();
	         if(flag == 1)step++;	
		       break;
		
		case 5:xunji_Init(99,65);if(IsStright())step++;break;
		case 6:	high_speed(50,50,1);break;
		
		case 7:flag = 0;
					 turn('l',1);
	         if(flag == 1)step++;	
		       break;
		case 8:xunji_Init(99,65);if(IsStright())step++;break;
		case 9:now_yaw = angle[2];high_speed(50,80,1);break;

		
		case 10:flag = 0;nowpingtai=5;
					 platform(now_yaw);
	         if(flag == 1)step++;	
		       break;
		
		case 11:flag=0;
						if(image[1]==5&&flag==0)ShakeHand();
						if(flag == 1)step++;
						if(image[1]!=5)step++;
						break;
		case 12:nowpingtai=0;stop();break;
	}
		if(step==12){
		step=0;
		Step++;
	}
}






//// 从平台3到平台6*
//void GO3TO6(){
//	switch(step)
//	{
//		case 0:if(go_down_platform()==1){xunji_Init(10,0);
//						time=mydelay(50);if(time==1){time_reset();step++;}}break;
//		case 1:	high_speed(200,100,1);break;
//			
//		case 2:flag=0;
//						turn_90('r',3);  
//						if(flag==1)step++;
//						break;
//		
//		case 3:flag = 0;
//					 doors();
//	         if(flag == 1)step++;	
//		       break;
//		case 4:flag=0;
//						turn_90('r',2);  
//						if(flag==1){xunji_Init(99,50);step++;}
//						break;
//		case 5:
//						flag = 0;
//						turn('l',2);
//						if(flag == 1)step++;	
//						break;
//		case 6:xunji_Init(99,50);step++;break;
//		case 7:
//						flag = 0;
//					 seesaw(1);
//	         if(flag == 1)step++;	
//		       break;
//		case 8:flag = 0;
//					 turn_90('l',1);
//	         if(flag == 1){now_yaw = get_now_yaw();step++;	}
//		       break;
//		case 9:flag = 0;			
//					 platform(now_yaw);
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 10:stop();break;
//	}
//		if(step==10){
//		step=0;
//		Step++;
//	}
//	}







//// 从平台4到平台5*
//void GO4TO5(){
//	switch(step)
//	{
//		case 0:if(go_down_platform()==1){xunji_Init(10,0);
//						time=mydelay(50);if(time==1){time_reset();step++;}}break;
//		case 1:high_speed(200,120,1);break;
//		
//		case 2: flag=0;
//						turn_90('l',3);
//						if(flag==1)step++;
//						break;
//		
//		case 3:flag = 0;
//					 doors();
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 4:flag=0;
//						turn_90('l',2);
//						if(flag==1)step++;
//						break;

//		
//		case 5:xunji_Init(99,65);if(IsStright())step++;break;
//		case 6:now_yaw = get_now_yaw();high_speed(100,120,1);break;
//		
//				
//		case 7:flag = 0;
//					 platform(now_yaw);
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 8:stop();break;
//	}
//		if(step==8){
//		step=0;
//		Step++;
//	}
//}






//// 从平台4到平台6*
//void GO4TO6(){
//	switch(step)
//	{
//	  case 0:if(go_down_platform()==1){xunji_Init(10,0);
//						time=mydelay(50);if(time==1){time_reset();step++;}}break;
//		case 1:	high_speed(200,100,1);break;
//			
//		case 2:flag=0;
//						turn_small_angle('l');
//						if(flag==1)step++;
//						break;
//		
//		case 3:flag = 0;
//					 doors();
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 4:xunji_Init(99,65);if(IsStright())step++;break;
//		case 5:	high_speed(50,120,1);break;
//		
//		case 6:flag = 0;
//					 turn('r',1);
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 7:xunji_Init(99,50);step++;break;
//		
//		case 8:flag = 0;
//					 seesaw(1);
//	         if(flag == 1)step++;	
//		       break;
//		case 9:flag = 0;
//					 turn_90('l',1);
//	         if(flag == 1){now_yaw = get_now_yaw();step++;	}
//		       break;
//		case 10:flag = 0;			
//					 platform(now_yaw);
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 11:stop();break;
//	}
//		if(step==11){
//		step=0;
//		Step++;
//	}
//}






//// 从平台5到平台7*    //还未调试 理论上可行  
//void GO5TO7(){
//	switch(step)
//	{
//		case 0:if(go_down_platform()==1){xunji_Init(10,0);
//						time=mydelay(50);if(time==1){time_reset();step++;}}break;
//		case 1:high_speed(50,220,1);break;
//		
//		case 2:flag = 0;
//					 turn_90('l',1);
//	         if(flag == 1)step++;	
//		       break;
//						
//		case 3:xunji_Init(99,65);if(IsStright())step++;break;
//		case 4:high_speed(15,25,1);break;
//						
//		case 5:flag = 0;
//					 slop(4);
//	         if(flag == 1){now_yaw = get_now_yaw();nowpingtai=7;step++;}
//		       break;
//					 			 
//		case 6:xunji_Init(99,65);
//						flag=0;
//						decestrip();
//						if(flag==1)step++;
//						break;
//					 
//		case 7:flag = 0;
//					 platform(now_yaw);
//	         if(flag == 1){nowpingtai=0;step++;}
//		       break;
//		case 8:stop();break;	
//	}
//	if(step==8){
//		step=0;
//		Step++;
//	}
//}






//// 从平台6到平台5*    //还未调试 理论上可行
//void GO6TO5(){
//	switch(step)
//	{
//		case 0:if(go_down_platform()==1)step++;break;
//		
//		case 1:flag = 0;
//					 turn('l',3);
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 2:nowpingtai=6;xunji_Init(99,75);
//						if(hd_qian[0]==0){nowpingtai=0;step++;}						
//						break;
//						
//		case 3:xunji_Init(99,65);if(IsStright()){now_yaw = get_now_yaw();step++;}break;
//		case 4:high_speed(50,400,1);break;
//		
//		case 5:flag = 0;
//					 platform(now_yaw);
//	         if(flag == 1){nowpingtai=0;step++;}
//		       break;
//		case 6:stop();break;	
//	}
//	if(step==6){
//		step=0;
//		Step++;
//	}
//}








// 从平台6到平台7*
void GO6TO7(){
	switch(step)
	{
		case 0:flag=0;
					go_down_platform();
					if(flag==1){xunji_Init(99,65);step++;}break;
		
		case 1:flag = 0;
					 turn('l',3);
	         if(flag == 1)step++;	
		       break;
		
		case 2:nowpingtai=6;xunji_Init(99,50);
						step++;						
						break;
					
		case 3:xunji_Init(99,65);
						flag=0;
						decestrip();
						if(flag==1)step++;
						break;
					
		case 4:xunji_Init(99,50);if(hd_qian[0]==0){nowpingtai=0;step++;}break;
		
		
		case 5:xunji_Init(99,65);if(IsStright())step++;break;
		case 6:high_speed(25,120,1);break;
			
		case 7:flag = 0;
					 turn_90('r',1);
	         if(flag == 1)step++;	
		       break;
						
		case 8:xunji_Init(99,65);if(IsStright())step++;break;
		case 9:high_speed(15,50,1);break;
						
		case 10:flag = 0;
					 slop(4);
	         if(flag == 1){now_yaw = angle[2];step++;}
		       break;
		case 11:flag = 0;nowpingtai=7;
					 platform(now_yaw);
	         if(flag == 1){nowpingtai=0;step++;}
		       break;
		case 12:flag=0;
						if(image[2]==7&&flag==0)ShakeHand();
						if(flag == 1)step++;
						if(image[2]!=7)step++;
						break;
		case 13:nowpingtai=0;stop();break;
	}
	if(step==13){
		step=0;
		Step++;
	}
}






//// 从平台5到平台8*    //还未调试 理论上可行
//void GO5TO8(){
//	switch(step)
//	{
//		case 0:if(go_down_platform()==1){xunji_Init(10,0);
//						time=mydelay(50);if(time==1){time_reset();step++;}}break;
//		case 1:high_speed(50,220,1);break;
//		
//		case 2:flag = 0;
//					 turn_90('l',1);
//	         if(flag == 1)step++;	
//		       break;
//						
//		case 3:xunji_Init(99,65);if(IsStright())step++;break;
//		case 4:high_speed(15,45,1);break;
//						
//		case 5:flag = 0;
//					 slop(3);
//	         if(flag == 1){now_yaw = get_now_yaw();nowpingtai=8;step++;}
//		       break;
//		case 6:flag = 0;
//					 platform(now_yaw);
//	         if(flag == 1){nowpingtai=0;step++;}
//		       break;
//		case 7:stop();break;	
//	}
//	if(step==7){
//		step=0;
//		Step++;
//	}
//}







//// 从平台6到平台8*
//void GO6TO8(){
//	switch(step)
//	{
//		case 0:if(go_down_platform()==1)step++;break;
//		
//		case 1:flag = 0;
//					 turn('l',3);
//	         if(flag == 1)step++;	
//		       break;
//		
//		case 2:nowpingtai=6;xunji_Init(99,60);
//						if(hd_qian[0]==0&&hd_qian[3]+hd_qian[4]+hd_qian[5]<=2){nowpingtai=0;step++;}						
//						break;
//						
//		case 3:xunji_Init(99,65);if(IsStright())step++;break;
//		case 4:high_speed(50,170,1);break;
//			
//		case 5:flag = 0;
//					 turn_90('r',1);
//	         if(flag == 1)step++;	
//		       break;
//						
//		case 6:xunji_Init(99,65);if(IsStright())step++;break;
//		case 7:high_speed(15,30,1);break;
//						
//		case 8:flag = 0;
//					 slop(3);
//	         if(flag == 1){now_yaw = get_now_yaw();nowpingtai=8;step++;}
//		       break;
//		case 9:flag = 0;
//					 platform(now_yaw);
//	         if(flag == 1){nowpingtai=0;step++;}
//		       break;
//		case 10:stop();break;	
//	}
//	if(step==10){
//		step=0;
//		Step++;
//	}
//}






// 从平台7到平台8* 
void GO7TO8(){
	switch(step)
	{
		case 0:xunji_Init(4,0);
					 time=mydelay(300);if(time==1){time_reset();step++;}break;
		
		case 1:xunji_Init(99,65);
						flag=0;
						decestrip();
						if(flag==1)step++;
						break;
		case 2:xunji_Init(99,60);if(hd_qian[0]+hd_qian[1]+hd_qian[2]+hd_qian[3]==0)step++;
		case 3:flag = 0;
					 slop(2);
	         if(flag == 1){now_yaw = angle[2];step++;}
		       break;
		case 4:flag = 0;nowpingtai = 8;
					 platform(now_yaw);
	         if(flag == 1){nowpingtai=0;step++;}
		       break;
		case 5:flag=0;
						if(image[2]==8&&flag==0)ShakeHand();
						if(flag == 1)step++;
						if(image[2]!=8)step++;
						break;
		case 6:nowpingtai=0;stop();break;	
	}
	if(step==6){
		step=0;
		Step++;
	}
}






//// 从平台7回家**      //下平台和斜面还未调试其他理论上可行
//void gohome7(){
//	switch(step)
//	{
//		case 0:xunji_Init(4,0);
//					 time=mydelay(500);if(time==1&&(angle[1]<10||angle[1]>50)){time_reset();step++;}break;
//		
//		case 1:xunji_Init(99,65);
//						flag=0;
//						decestrip();
//						if(flag==1){nowpingtai=7;step++;}
//						break;
//			
//		case 2:flag = 0;
//					 slop(5);
//	         if(flag == 1){nowpingtai=0;step++;}
//		       break;
//				
//		case 3:xunji_Init(99,65);if(IsStright())step++;break;
//		case 4:high_speed(15,45,1);break;
//					 
//		case 5:flag = 0;
//					 turn_90('l',1);
//	         if(flag == 1)step++;	
//		       break;
//					 
//		case 6:flag = 0;
//					 turn_90('l',2);
//	         if(flag == 1)step++;	
//		       break;
//					 
//		case 7:flag = 0;
//					 doors();
//	         if(flag == 1)step++;	
//		       break;
//		case 8:flag = 0;
//					 turn_90('l',2);
//	         if(flag == 1)step++;	
//		       break;
//					 
//		case 9:flag = 0;
//					 slop(5);
//	         if(flag == 1){nowpingtai=0;step++;}
//		       break;	

//		case 10:flag = 0;
//					 seesaw(2);
//	         if(flag == 1)step++;	
//		       break;
//					 
//		case 11:flag = 0;
//					 turn_small_angle2();
//	         if(flag == 1){now_yaw = get_now_yaw();nowpingtai=8;step++;}
//		       break;
//		case 12:flag = 0;
//					 platform(now_yaw);
//	         if(flag == 1){nowpingtai=0;step++;}
//		       break;
//		case 13:stop();break;	
//	}
//	if(step==13){
//		step=0;
//		Step++;
//	}
//}





// 从平台8回家**      //下平台和斜面还未调试其他理论上可行
void gohome8(){
	switch(step)
	{
		case 0:xunji_Init(4,0);
					 time=mydelay(950);if(time==1&&(angle[1]<10||angle[1]>50))
							{time_reset();nowpingtai=8;step++;}break;			
		case 1:flag = 0;
					 slop(5);
	         if(flag == 1){nowpingtai=0;step++;}
		       break;
				
		case 2:xunji_Init(99,65);if(IsStright())step++;break;
		case 3:high_speed(15,30,1);break;
					 
		case 4:flag = 0;
					 turn_90('l',1);
	         if(flag == 1)step++;	
		       break;
		
		case 5:xunji_Init(99,65);if(IsStright())step++;break;
		case 6:high_speed(15,30,1);break;		
					 
		case 7:flag = 0;
					 turn_90('r',2);
	         if(flag == 1)step++;	
		       break;
					 
		case 8:flag = 0;
					 doors();
	         if(flag == 1)step++;	
		       break;
					 
		//case 99:xunji_Init(10,0);time=mydelay(100000);if(time==1){time_reset();step=9;}break;
		case 9:xunji_Init(99,50);time=mydelay(50);if(time==1){time_reset();step++;}break;
		
		case 10:flag = 0;
					 turn_90('r',2);
	         if(flag == 1)step++;	
		       break;
					 
		case 11:flag = 0;
					 slop(6);
	         if(flag == 1){nowpingtai=0;step++;}
		       break;	

		case 12:flag = 0;
					 seesaw(2);
	         if(flag == 1)step++;	
		       break;
					 
		case 13:flag = 0;
					 turn_small_angle2();
	         if(flag == 1){now_yaw = angle[2];nowpingtai=8;step++;}
		       break;
		case 14:flag = 0;nowpingtai=1;
					 platform(now_yaw);
	         if(flag == 1){nowpingtai=0;step++;}
		       break;
		case 15:stop();break;	
	}
	if(step==15){
		step=0;
		Step++;
	}
}