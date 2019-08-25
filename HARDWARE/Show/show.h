#ifndef _SHOW_H
#define _SHOW_H

#include "sys.h"

void lcdspeed(void);
void drawspeed(void);
void USART(void);
void IncPIDInit(void);
int IncPIDCalc(int NextPoint);
void controlD(void);
void controlI(void);
void controlP(void);
void controlSpeed(void);
void controlAngle(void);
void scan(void);
void ScanAll(void);


#endif
