#ifndef __MODULE_H
#define __MODULE_H
#include "sys.h"



typedef struct step{
	
	int turn_small_step;  // 小角度转弯
	int bridge_step;  // 长桥
	int seesaw_step;  // 跷跷板
	int platform_step;  // 平台
	int slop_step;  // 斜路面
	int decestrip_step;  // 减速带
	int door_step;  // 门
	int turn_step;
	int turn_90_step;
	int go_down_platform;
	int shakehead_step;
	int shakehand_step;
}step_struct;

extern int kaca;
extern int treasure;
extern int Step;
extern int flag;//用于检验是否步骤完成
extern unsigned char sign,t,he;
extern double angle[3];
extern int delaytime;
extern u8 time,nowpingtai,speed_step;
extern int delaytime2;
extern u8 time2;
extern int shakehead_flag;

int mydelay2(int time);
void time_reset2(void);
void ShakeHead(void);
void ShakeHand(void);
void GetTreasure(void);
int IsStright(void);
void go_down_platform(void);
void doors(void);
int mydelay(int time);
void time_reset(void);
void high_speed(int low_speed_time,int high_speed_time,u8 gear);
void gohome8(void);
void gohome7(void);
void turn_small_angle2(void);
void turn_small_angle(char direction);
void decestrip(void);
void slop(int direction);
void stoptime(int time);
void turn(char direction, int turn_num);
void turn_90(char direction, int mode);
void seesaw(int mode);//跷跷板
void platform(int z_angle);//平台
void bridge(void);//长桥
#endif
