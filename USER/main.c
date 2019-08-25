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

extern u8  TIM4CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ	


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
  //TIM3_PWM_Init(4799,0);//ͨ�ö�ʱ������Ƶʱ��Ƶ��72000000��PWMƵ��=72000000/4800=15Khz�Զ�װ��ֵ4799���жϼ���Ƶ��4799+1=4800��
	//��4799��0����ʾ0������4799��ʱ��Ϊ����PWM��������
	TIM5_Encoder_Init(0xffff,72-1);
	LCD_Init();
	KEY_Init();
	AT24CXX_Init();
	Remote_Init();
	DCMOTOR_BRUSH_TIMx_PWM_Init(); 
	IncPIDInit();
	/* ʹ��PWM��� */
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




