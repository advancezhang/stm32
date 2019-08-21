#ifndef _SHOW_H
#define _SHOW_H

#include "sys.h"

void lcdspeed(void);
void drawspeed(void);
void USART(void);
void IncPIDInit(void);
int IncPIDCalc(int NextPoint);


#endif
