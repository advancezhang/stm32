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
#include "brush.h" 

typedef struct 
{
   __IO int      SetPoint;                                 //设定目标 Desired Value
   __IO double   Proportion;                               //比例常数 Proportional Const
   __IO double   Integral;                                 //积分常数 Integral Const
   __IO double   Derivative;                               //微分常数 Derivative Const
   __IO int      LastError;                                //Error[-1]
   __IO int      PrevError;                                //Error[-2]
}PID;


float P_DATA=-1.5;                               //P参数
float I_DATA=0.8;                                //I参数
float D_DATA=0.4;                               //D参数

__IO uint16_t dcmotor_speed=3000;
__IO double encoder_speed=0;

static PID sPID;
static PID *sptr = &sPID;

/**************PID参数初始化********************************/
void IncPIDInit(void) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //比例常数 Proportional Const
    sptr->Integral=I_DATA;        //积分常数  Integral Const
    sptr->Derivative=D_DATA;      //微分常数 Derivative Const
    sptr->SetPoint=50;           //设定目标Desired Value
}
/********************增量式PID控制设计************************************/
int IncPIDCalc(int NextPoint) 
{
  int iError,iIncpid;                                 //当前误差
  iError=sptr->SetPoint-NextPoint;                    //增量计算
  iIncpid=(sptr->Proportion * iError)                 //E[k]项
              -(sptr->Integral * sptr->LastError)     //E[k-1]项
              +(sptr->Derivative * sptr->PrevError);  //E[k-2]项
              
  sptr->PrevError=sptr->LastError;                    //存储误差，用于下次计算
  sptr->LastError=iError;
  return(iIncpid);                                    //返回增量值
}

extern u8  TIM4CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值	
void lcdspeed(void);
void drawspeed(void);

u16 adcx;
float temp;
float angle;
u8 buffer[7];
u8 str[7];
u16 count=47;

int main(void)
{
  float para;
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
  TIM3_PWM_Init(4799,0);//通用定时器不分频时钟频率72000000。PWM频率=72000000/4800=15Khz自动装载值4799（中断计算频率4799+1=4800）
	//（4799，0）表示0计数到4799的时间为计算PWM波的周期
	TIM4_Encoder_Init(0xffff,72-1);
	LCD_Init();
	KEY_Init();
	DCMOTOR_BRUSH_TIMx_PWM_Init(); 
	IncPIDInit();
	/* 使能PWM输出 */
  DCMOTOR_25GA370_Contrl(4,0,0); 
	

	while(1)
	{
		lcdspeed();
		drawspeed();
		para=IncPIDCalc(temp);
	  /* 根据增量数值调整当前电机速度 */
		//if((para<-3)||(para>3)) // 不做 PID 调整，避免误差较小时频繁调节引起震荡。
		//{
			dcmotor_speed +=para;  
		//}
		if(dcmotor_speed>60000)dcmotor_speed=0;      
    DCMOTOR_25GA370_Contrl(1,1,dcmotor_speed);
  }
	}

void lcdspeed(void)
{
	adcx=TIM4->CNT;
	temp=(float)adcx/10;
	if(temp>2000)
	{
		temp=6553.5-temp;
		sprintf((char*)buffer,"%.2f",temp);
	  LCD_ShowString(95,35,85,40,24,buffer);
	}
	else
	{
		sprintf((char*)buffer,"%.2f",temp);
		LCD_ShowString(95,35,85,40,24,buffer);
	}
	TIM4->CNT=0;
	delay_ms(1000);
}
void drawspeed(void)
{
	u8 i;
	u8 a;
	count++;
	LCD_DrawLine(count,450-temp*2,count+1,450-temp*2);
	if(count>470)
	{
		count=47;
		LCD_Fill(47,212,468,448,WHITE);
	}
	for(i=0;i<=10;i++)
	{
		LCD_DrawLine(45,i*20+230,33,i*20+230);
	}
	for(a=0;a<=35;a++)
	{
		LCD_DrawLine(45,a*5+500,33,a*5+500);
		LCD_DrawLine(45,590,28,590);
	}
	sprintf((char*)str,"%d",sptr->SetPoint);
	LCD_ShowString(95,160,85,40,24,str);
	LCD_ShowString(15,35,85,40,24,"Speed:");
	LCD_ShowString(245,35,85,40,24,"Angle:");
	LCD_ShowString(15,135,65,40,24,"Set   Speed:");
	LCD_ShowString(245,135,65,40,24,"Set   Angle:");
	LCD_ShowString(20,450,85,40,24,"0");
	LCD_ShowString(0,340,85,40,24,"50");
	LCD_ShowString(0,240,85,40,24,"100");
	LCD_ShowString(20,670,60,30,16,"0");
	LCD_ShowString(0,580,60,30,16,"180");
	LCD_ShowString(0,485,60,30,16,"360");
	LCD_ShowString(15,720,77,40,24,"KP");
	LCD_ShowString(169,720,77,40,24,"KI");
	LCD_ShowString(323,720,77,40,24,"KD");
	LCD_ShowString(92,720,77,40,24,"-1.5");
	LCD_ShowString(246,720,77,40,24,"0.8");
	LCD_ShowString(400,720,77,40,24,"0.4");
	LCD_DrawRectangle(10,10,470,100);
	LCD_DrawRectangle(10,110,470,200);
	LCD_DrawRectangle(45,210,470,450);
	LCD_DrawRectangle(45,470,470,680);
	LCD_DrawRectangle(10,700,470,790);
	LCD_DrawLine(87,690,87,780);
	LCD_DrawLine(164,690,164,780);
	LCD_DrawLine(241,690,241,780);
	LCD_DrawLine(318,690,318,780);
	LCD_DrawLine(395,690,395,780);
	LCD_DrawLine(90,10,90,100);
	LCD_DrawLine(240,10,240,100);
	LCD_DrawLine(320,10,320,100);
	LCD_DrawLine(90,110,90,200);
	LCD_DrawLine(240,110,240,200);
	LCD_DrawLine(320,110,320,200);
	
}

