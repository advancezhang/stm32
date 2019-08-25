#include "delay.h"
#include "usart.h"
#include "encoder.h"
#include "key.h"
#include "lcd.h"
#include "stdio.h"
#include "brush.h" 
#include "24cxx.h"
#include "usmart.h"	 
#include "24cxx.h"
#include "show.h"
#include "remote.h"

extern void lcdspeed(void);
extern void drawspeed(void);
extern void USART(void);
extern void IncPIDInit(void);
extern int IncPIDCalc(int NextPoint);
extern void KeyAction(void);

extern u8  TIM4CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值	


extern float temp;
float angle;


extern void controlD(void);
extern void controlI(void);
extern void controlP(void);
extern void controlSpeed(void);
extern void controlAngle(void);
extern void ScanAll(void);
extern void scan(void);
extern u8 Break;

int main(void)
{
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
  //TIM3_PWM_Init(4799,0);//通用定时器不分频时钟频率72000000。PWM频率=72000000/4800=15Khz自动装载值4799（中断计算频率4799+1=4800）
	//（4799，0）表示0计数到4799的时间为计算PWM波的周期
	TIM5_Encoder_Init(0xffff,72-1);
	LCD_Init();
	KEY_Init();
	AT24CXX_Init();
	Remote_Init();
	DCMOTOR_BRUSH_TIMx_PWM_Init(); 
	IncPIDInit();
	/* 使能PWM输出 */
  DCMOTOR_25GA370_Contrl(4,0,0); 
	

	while(1)
	{
		lcdspeed();
		drawspeed();
		scan();
		if(Break)
		{
		  USART();
		}
		else
		{
			ScanAll();
		}
  }
}




