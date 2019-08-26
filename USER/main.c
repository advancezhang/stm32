#include "delay.h"
#include "usart.h"
#include "encoder.h"
#include "lcd.h"
#include "stdio.h"
#include "brush.h" 
#include "24cxx.h"
#include "usmart.h"	 
#include "show.h"
#include "remote.h"


extern void ScanAll(void);
extern void scan(void);
extern u8 Break;

int main(void)
{
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	TIM5_Encoder_Init(0xffff,72-1);
	LCD_Init();
	AT24CXX_Init();
	Remote_Init();
	DCMOTOR_BRUSH_TIMx_PWM_Init(); 
	IncPIDInit();
	/* 使能PWM输出 */
  DCMOTOR_25GA370_Contrl(2,0,0); 
	

	while(1)
	{
		lcdspeed();
		drawspeed();
		scan();
		if(Break)//当外星人头像按下之后切换到按键控制，开关键按下切换到上位机控制
		{
		  USART();
		}
		else
		{
			ScanAll();
		}
  }
}















