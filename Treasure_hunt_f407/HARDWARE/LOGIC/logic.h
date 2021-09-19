#ifndef __LOGIC_H
#define __LOGIC_H
#include "sys.h"
extern int start;
extern u8 image[3];
extern u8 all_step,step;
extern int intersection;

void GO1TO2(void);
void GO2TO3(void);
void GO4TO3(void);
void GO4TO5(void);
void GO5TO7(void);
void GO7TO8(void);
void GO6TO5(void);
void GO2TO4(void);
void GO3TO5(void);
void GO3TO6(void);
void GO4TO6(void);
void GO5TO8(void);
void GO6TO7(void);
void GO6TO8(void);
void GO5TO6(void);
void all(void);
void all_only_three_treassure(void);
void all_only_three_treassure_and_78(void);
#endif
