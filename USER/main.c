//#include "delay.h"
//#include "key.h"
//#include "sys.h"
//#include "usart.h"
//#include "timer.h"
//#include "encoder.h"
////#include "pid.h"
// 	
//	


//int main(void)
//{		
//	u16 led0pwmval=3840;
//	u16 cycle=4800;
//	int duty_cycle,b,n;
//	vu8 key=0;
//	// LED_Init();
//	delay_init();	    	 //��ʱ������ʼ��	
//	KEY_Init();              //������ʼ��	 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
//	TIM3_PWM_Init(cycle-1,0);	 //ͨ�ö�ʱ������Ƶʱ��Ƶ��72000000��PWMƵ��=72000000/4800=15Khz�Զ�װ��ֵ4799���жϼ���Ƶ��4799+1=4800��
//	//��4799��0����ʾ0������4799��ʱ��Ϊ����PWM��������
//	key=KEY_Scan(0);	//�õ���ֵ  ��֧������
//  while(1)
//  {
//		key=KEY_Scan(0);	//�õ���ֵ  ��֧������
//		//LED1=!LED1;
//		if(key)
//		{						   
//		switch(key)
//		{				 

//			case KEY2_PRES:	//������תPB4��
//				
//			if(b==2&&led0pwmval>2400)//�����ת�ٶȹ����ȼ��٣�����ת����ɾ��
//			{
//				n=led0pwmval;	
//				led0pwmval=2400;	
//				TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//				TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0	
//				duty_cycle=led0pwmval*100/cycle;//ռ�ձ�
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//���ռ�ձ�
//				printf("\r\n\r\n");//���뻻��
//				delay_ms(500);	
//				led0pwmval=n;
//			}                                    //

//			TIM_SetCompare2(TIM3,0);//PB5ռ�ձ�Ϊ0   ��
//			TIM_SetCompare1(TIM3,led0pwmval);//PB4ռ�ձ�Ϊled0pwmval/duty_cycle
//			duty_cycle=led0pwmval*100/cycle;//ռ�ձ�
//			printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//���ռ�ձ�
//			printf("\r\n\r\n");//���뻻��
//			delay_ms(1864);	
//			b=1;//�ж���ת��	
//			break;
//			
//	    case KEY1_PRES:	//���Ʒ�תPB5��
//				
//			if(b==1&&led0pwmval>2400)//�����ת�ٶȹ����ȼ��٣���ת����ɾ��
//      {			
//				n=led0pwmval;	
//				led0pwmval=2400;	
//				TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//				TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0	
//				duty_cycle=led0pwmval*100/cycle;//ռ�ձ�
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//���ռ�ձ�
//				printf("\r\n\r\n");//���뻻��
//				delay_ms(500);	
//				led0pwmval=n;
//      }                                    //

//			TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//			TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0	
//			duty_cycle=led0pwmval*100/cycle;//ռ�ձ�
//			printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//���ռ�ձ�
//			printf("\r\n\r\n");//���뻻��
//			delay_ms(1864);	
//			b=2;//�жϷ�ת��				
//			break; 
//			
//			case WKUP_PRES:	//���Ƹ���
//			{
//				led0pwmval=led0pwmval+480;//led0pwmvalֵ����%10
//				if(led0pwmval>4800)//��led0pwmval������4800����ֵΪ4800	
//				{
//			    led0pwmval=4800;
//		    }				
//				if(b==1)//��ת
//				{
//				TIM_SetCompare2(TIM3,0);//PB5ռ�ձ�Ϊ0  ��
//						TIM_SetCompare1(TIM3,led0pwmval);//PB4ռ�ձ�Ϊled0pwmval/duty_cycle
//				}
//				else//��ת
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//								TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0	
//				}
//		
//				duty_cycle=led0pwmval*100/cycle;//ռ�ձ�
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//���ռ�ձ�
//				printf("\r\n\r\n");//���뻻��
//				delay_ms(1864);	

//				}
//				break;

//			case KEY0_PRES:	//���Ƶ���
//			{
//				led0pwmval=led0pwmval-480;	//led0pwmvalֵ�Լ�%10
//				if(led0pwmval<480)//��led0pwmvalС��480����ֵΪ0	
//				{
//					led0pwmval=0;
//				}		
//			  if(b==1)//��ת
//				{
//					TIM_SetCompare2(TIM3,0);//PB5ռ�ձ�Ϊ0  ��
//					TIM_SetCompare1(TIM3,led0pwmval);//PB4ռ�ձ�Ϊled0pwmval/duty_cycle
//				}
//				else//��ת
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//					TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0	
//				}
//				duty_cycle=led0pwmval*100/cycle;
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//���ռ�ձ�
//				printf("\r\n\r\n");//���뻻��
//				delay_ms(1864);	
//			}
//				break;
//			}
//	  }else delay_ms(10); 					 
//  }
//}
//	while(1)
//	{
//		lcdspeed();
//		key=KEY_Scan(0);	//�õ���ֵ  ��֧������
//		//LED1=!LED1;
//		if(key)
//		{						   
//		switch(key)
//		{				 

//			case KEY2_PRES:	//������תPB4��
//			TIM_SetCompare2(TIM3,0);//PB5ռ�ձ�Ϊ0   ��
//			TIM_SetCompare1(TIM3,led0pwmval);//PB4ռ�ձ�Ϊled0pwmval/duty_cycle
//			b=1;//�ж���ת��	
//			break;
//			
//	    case KEY1_PRES:	//���Ʒ�תPB5��
//			TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//			TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0		
//			b=2;//�жϷ�ת��				
//			break; 
//			
//			case WKUP_PRES:	//���Ƹ���
//			{
//				led0pwmval=led0pwmval+480;//led0pwmvalֵ����%10
//				if(led0pwmval>4800)//��led0pwmval������4800����ֵΪ4800	
//				{
//			    led0pwmval=4800;
//		    }				
//				if(b==1)//��ת
//				{
//				TIM_SetCompare2(TIM3,0);//PB5ռ�ձ�Ϊ0  ��
//						TIM_SetCompare1(TIM3,led0pwmval);//PB4ռ�ձ�Ϊled0pwmval/duty_cycle
//				}
//				else//��ת
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//								TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0	
//				}
//				}
//				break;

//			case KEY0_PRES:	//���Ƶ���
//			{
//				led0pwmval=led0pwmval-480;	//led0pwmvalֵ�Լ�%10
//				if(led0pwmval<480)//��led0pwmvalС��480����ֵΪ0	
//				{
//					led0pwmval=0;
//				}		
//			  if(b==1)//��ת
//				{
//					TIM_SetCompare2(TIM3,0);//PB5ռ�ձ�Ϊ0  ��
//					TIM_SetCompare1(TIM3,led0pwmval);//PB4ռ�ձ�Ϊled0pwmval/duty_cycle
//				}
//				else//��ת
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5ռ�ձ�Ϊled0pwmval/duty_cycle  ��
//					TIM_SetCompare1(TIM3,0);//PB4ռ�ձ�Ϊ0	
//				}
//			}
//				break;
//			}
//	  }else delay_ms(10); 					 
//  }
#include "delay.h"
#include "usart.h"
#include "encoder.h"
#include "timer.h"
#include "key.h"
#include "lcd.h"
#include "stdio.h"
#include "pid.h"

extern u8  TIM4CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ	
void lcdspeed(void);

//u16 led0pwmval=3840;
//u16 cycle=4800;
//int b;
//vu8 key=0;
u8 actual=50;
u16 adcx;
float temp;
float angle;
u8 buffer[7];
u8 str[7];
	
int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
  //TIM3_PWM_Init(cycle-1,0);//ͨ�ö�ʱ������Ƶʱ��Ƶ��72000000��PWMƵ��=72000000/4800=15Khz�Զ�װ��ֵ4799���жϼ���Ƶ��4799+1=4800��
	//��4799��0����ʾ0������4799��ʱ��Ϊ����PWM��������
	TIM4_Encoder_Init(0xffff,72-1);
	LCD_Init();
	KEY_Init();
	
	LCD_ShowString(15,35,85,40,24,"Speed:");
	LCD_ShowString(245,35,85,40,24,"Angle:");
	LCD_ShowString(15,135,65,40,24,"Set   Speed:");
	LCD_ShowString(245,135,65,40,24,"Set   Angle:");
	LCD_DrawRectangle(10,10,470,100);
	LCD_DrawRectangle(10,110,470,200);
	LCD_DrawRectangle(10,210,470,450);
	LCD_DrawRectangle(10,510,470,750);
	LCD_DrawLine(90,10,90,100);
	LCD_DrawLine(240,10,240,100);
	LCD_DrawLine(320,10,320,100);
	LCD_DrawLine(90,110,90,200);
	LCD_DrawLine(240,110,240,200);
	LCD_DrawLine(320,110,320,200);
	while(1)
	{
		lcdspeed();
		LCD_ShowString(95,160,85,40,24,"50");					 
  }
	}

void lcdspeed(void)
{
	adcx=TIM4->CNT;
	temp=(float)adcx/10;
	//angle=adcx*36;
	sprintf((char*)buffer,"%.2f",temp);
	//sprintf(str,"%.1f",angle);
	LCD_ShowString(95,35,85,40,24,buffer);
	//LCD_ShowString(325,35,95,40,24,str);
	TIM4->CNT=0;
	delay_ms(1000);
}
void PID_init(){
		pid.SetSpeed=0.0;
		pid.ActualSpeed=0.0;
		pid.err=0.0;
		pid.err_last=0.0;
		pid.voltage=0.0;
		pid.integral=0.0;
		pid.Kp=0.2;
		pid.Ki=0.015; 
		pid.Kd=0.2;
}
float PID_realize(float speed){
	pid.SetSpeed=speed;
	pid.err=pid.SetSpeed-pid.ActualSpeed;
	pid.integral+=pid.err;
	pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
	pid.err_last=pid.err;
	pid.ActualSpeed=pid.voltage*1.0;
	return pid.ActualSpeed;
}	

