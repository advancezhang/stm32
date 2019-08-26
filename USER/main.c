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
	/* ʹ��PWM��� */
  DCMOTOR_25GA370_Contrl(2,0,0); 
	

	while(1)
	{
		lcdspeed();
		drawspeed();
		scan();
		if(Break)//��������ͷ����֮���л����������ƣ����ؼ������л�����λ������
		{
		  USART();
		}
		else
		{
			ScanAll();
		}
  }
}















