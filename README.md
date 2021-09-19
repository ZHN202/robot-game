# robot-game
# robot-game

*******************************************************************

							硬件情况
			
		核心板：STM32F407
		
		电机：四个那英特电机
		
		色标：车前方左右各两个色标    左：SBL         右：SBR
		
		灰度：前后两个八路灰度板      前：hd_qian[x]  后：hd_hou[x] 
			  左右各一个单路灰度      左：HDL         右：HDR


​		
​		

*******************************************************************

							软件情况



@ trailing.c         @ led.c            @ oled.c          @ pwm.c

	循迹             端口定义           OLED显示          PWM波输出

  



@ timer.c            @ pid.c            @ module.c        @ logic.c

定时器定义           PID算法            各个路段的模块    循迹的逻辑
	
	
@ button.c           @ usart.c

按键的定义           陀螺仪定义
	
	

***************************************************************************

							！注意！

陀螺仪  angle[1]表示小车俯仰角 当小车水平时angle[1]会在1，2，58，59之间变化

几个重要变量
flag用于判断路段模块是否完成
step循迹模块中步骤
Step总的循迹步骤
	
	
各个路段模块的函数形式为：
	Name(){
		switch(constep.xxx_step){
			case 0:xxxxx;break;
				......
		    case x:break;
			}
		if(constep.xxx_step==x && flag==0){
			constep.xxx_step==0;
			flag=1;
			}
		}
flag=1表示一个模块完成
各个模块的使用方法：
	flag=0;
	Name();
	if(flag==1){step++;}
	
循迹逻辑的函数形式为：
	GOATOB(){
		switch(step){
			case 0:xxxxx;break;  // 可放入模块
			     ......
			case x:break;
			}
		if(step==x){
			Step++;
			step=0;
			}
		}
在循迹逻辑中使用定时高速循迹函数
high_speed(low_speed_time, high_speed_time, mode)时
函数中已经内嵌step++


几个关键函数：
high_speed(low_speed_time, high_speed_time, mode)定时高速循迹  // 使用前最好先判断车身位置是否正
xunji_Init(mode, x)循迹模式设置
(99, speed)  // 以speed的速度循迹
(11, speed)  // 以speed的速度用色标循迹
(4, 0)  // 专门用于高平台下坡
(0, 0)  // 不执行操作转弯前必须设置
(100, speed)  // 以speed的速度前进不循迹
其它mode已内嵌于其它函数不要改动！！！

*******************************************************************************************

							存在的问题

还有斜面的函数未完成
转九十度弯的函数需要完善
上高平台的函数未完成

速度还可以往上调
	
