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
//	delay_init();	    	 //延时函数初始化	
//	KEY_Init();              //按键初始化	 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	uart_init(115200);	 //串口初始化为115200
//	TIM3_PWM_Init(cycle-1,0);	 //通用定时器不分频时钟频率72000000。PWM频率=72000000/4800=15Khz自动装载值4799（中断计算频率4799+1=4800）
//	//（4799，0）表示0计数到4799的时间为计算PWM波的周期
//	key=KEY_Scan(0);	//得到键值  不支持连按
//  while(1)
//  {
//		key=KEY_Scan(0);	//得到键值  不支持连按
//		//LED1=!LED1;
//		if(key)
//		{						   
//		switch(key)
//		{				 

//			case KEY2_PRES:	//控制正转PB4高
//				
//			if(b==2&&led0pwmval>2400)//如果反转速度过大，先减速，后正转，可删除
//			{
//				n=led0pwmval;	
//				led0pwmval=2400;	
//				TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//				TIM_SetCompare1(TIM3,0);//PB4占空比为0	
//				duty_cycle=led0pwmval*100/cycle;//占空比
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//输出占空比
//				printf("\r\n\r\n");//插入换行
//				delay_ms(500);	
//				led0pwmval=n;
//			}                                    //

//			TIM_SetCompare2(TIM3,0);//PB5占空比为0   正
//			TIM_SetCompare1(TIM3,led0pwmval);//PB4占空比为led0pwmval/duty_cycle
//			duty_cycle=led0pwmval*100/cycle;//占空比
//			printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//输出占空比
//			printf("\r\n\r\n");//插入换行
//			delay_ms(1864);	
//			b=1;//判断正转用	
//			break;
//			
//	    case KEY1_PRES:	//控制反转PB5高
//				
//			if(b==1&&led0pwmval>2400)//如果正转速度过大，先减速，后反转，可删除
//      {			
//				n=led0pwmval;	
//				led0pwmval=2400;	
//				TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//				TIM_SetCompare1(TIM3,0);//PB4占空比为0	
//				duty_cycle=led0pwmval*100/cycle;//占空比
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//输出占空比
//				printf("\r\n\r\n");//插入换行
//				delay_ms(500);	
//				led0pwmval=n;
//      }                                    //

//			TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//			TIM_SetCompare1(TIM3,0);//PB4占空比为0	
//			duty_cycle=led0pwmval*100/cycle;//占空比
//			printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//输出占空比
//			printf("\r\n\r\n");//插入换行
//			delay_ms(1864);	
//			b=2;//判断反转用				
//			break; 
//			
//			case WKUP_PRES:	//控制高速
//			{
//				led0pwmval=led0pwmval+480;//led0pwmval值自增%10
//				if(led0pwmval>4800)//若led0pwmval大于于4800，赋值为4800	
//				{
//			    led0pwmval=4800;
//		    }				
//				if(b==1)//正转
//				{
//				TIM_SetCompare2(TIM3,0);//PB5占空比为0  正
//						TIM_SetCompare1(TIM3,led0pwmval);//PB4占空比为led0pwmval/duty_cycle
//				}
//				else//反转
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//								TIM_SetCompare1(TIM3,0);//PB4占空比为0	
//				}
//		
//				duty_cycle=led0pwmval*100/cycle;//占空比
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//输出占空比
//				printf("\r\n\r\n");//插入换行
//				delay_ms(1864);	

//				}
//				break;

//			case KEY0_PRES:	//控制低速
//			{
//				led0pwmval=led0pwmval-480;	//led0pwmval值自减%10
//				if(led0pwmval<480)//若led0pwmval小于480，赋值为0	
//				{
//					led0pwmval=0;
//				}		
//			  if(b==1)//正转
//				{
//					TIM_SetCompare2(TIM3,0);//PB5占空比为0  正
//					TIM_SetCompare1(TIM3,led0pwmval);//PB4占空比为led0pwmval/duty_cycle
//				}
//				else//反转
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//					TIM_SetCompare1(TIM3,0);//PB4占空比为0	
//				}
//				duty_cycle=led0pwmval*100/cycle;
//				printf("%d/%d==%d%%",led0pwmval,cycle,duty_cycle);//输出占空比
//				printf("\r\n\r\n");//插入换行
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
//		key=KEY_Scan(0);	//得到键值  不支持连按
//		//LED1=!LED1;
//		if(key)
//		{						   
//		switch(key)
//		{				 

//			case KEY2_PRES:	//控制正转PB4高
//			TIM_SetCompare2(TIM3,0);//PB5占空比为0   正
//			TIM_SetCompare1(TIM3,led0pwmval);//PB4占空比为led0pwmval/duty_cycle
//			b=1;//判断正转用	
//			break;
//			
//	    case KEY1_PRES:	//控制反转PB5高
//			TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//			TIM_SetCompare1(TIM3,0);//PB4占空比为0		
//			b=2;//判断反转用				
//			break; 
//			
//			case WKUP_PRES:	//控制高速
//			{
//				led0pwmval=led0pwmval+480;//led0pwmval值自增%10
//				if(led0pwmval>4800)//若led0pwmval大于于4800，赋值为4800	
//				{
//			    led0pwmval=4800;
//		    }				
//				if(b==1)//正转
//				{
//				TIM_SetCompare2(TIM3,0);//PB5占空比为0  正
//						TIM_SetCompare1(TIM3,led0pwmval);//PB4占空比为led0pwmval/duty_cycle
//				}
//				else//反转
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//								TIM_SetCompare1(TIM3,0);//PB4占空比为0	
//				}
//				}
//				break;

//			case KEY0_PRES:	//控制低速
//			{
//				led0pwmval=led0pwmval-480;	//led0pwmval值自减%10
//				if(led0pwmval<480)//若led0pwmval小于480，赋值为0	
//				{
//					led0pwmval=0;
//				}		
//			  if(b==1)//正转
//				{
//					TIM_SetCompare2(TIM3,0);//PB5占空比为0  正
//					TIM_SetCompare1(TIM3,led0pwmval);//PB4占空比为led0pwmval/duty_cycle
//				}
//				else//反转
//				{
//					TIM_SetCompare2(TIM3,led0pwmval);//PB5占空比为led0pwmval/duty_cycle  反
//					TIM_SetCompare1(TIM3,0);//PB4占空比为0	
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

extern u8  TIM4CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值	
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
  //TIM3_PWM_Init(cycle-1,0);//通用定时器不分频时钟频率72000000。PWM频率=72000000/4800=15Khz自动装载值4799（中断计算频率4799+1=4800）
	//（4799，0）表示0计数到4799的时间为计算PWM波的周期
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

