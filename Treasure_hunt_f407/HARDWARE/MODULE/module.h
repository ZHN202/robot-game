#ifndef __MODULE_H
#define __MODULE_H
#include "sys.h"



typedef struct step{
	
	int turn_small_step;  // С�Ƕ�ת��
	int bridge_step;  // ����
	int seesaw_step;  // ���ΰ�
	int platform_step;  // ƽ̨
	int slop_step;  // б·��
	int decestrip_step;  // ���ٴ�
	int door_step;  // ��
	int turn_step;
	int turn_90_step;
	int go_down_platform;
	int shakehead_step;
	int shakehand_step;
}step_struct;

extern int kaca;
extern int treasure;
extern int Step;
extern int flag;//���ڼ����Ƿ������
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
void seesaw(int mode);//���ΰ�
void platform(int z_angle);//ƽ̨
void bridge(void);//����
#endif
