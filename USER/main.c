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
#include "brush.h" 

typedef struct 
{
   __IO int      SetPoint;                                 //�趨Ŀ�� Desired Value
   __IO double   Proportion;                               //�������� Proportional Const
   __IO double   Integral;                                 //���ֳ��� Integral Const
   __IO double   Derivative;                               //΢�ֳ��� Derivative Const
   __IO int      LastError;                                //Error[-1]
   __IO int      PrevError;                                //Error[-2]
}PID;


float P_DATA=-1.5;                               //P����
float I_DATA=0.8;                                //I����
float D_DATA=0.4;                               //D����

__IO uint16_t dcmotor_speed=3000;
__IO double encoder_speed=0;

static PID sPID;
static PID *sptr = &sPID;

/**************PID������ʼ��********************************/
void IncPIDInit(void) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //�������� Proportional Const
    sptr->Integral=I_DATA;        //���ֳ���  Integral Const
    sptr->Derivative=D_DATA;      //΢�ֳ��� Derivative Const
    sptr->SetPoint=50;           //�趨Ŀ��Desired Value
}
/********************����ʽPID�������************************************/
int IncPIDCalc(int NextPoint) 
{
  int iError,iIncpid;                                 //��ǰ���
  iError=sptr->SetPoint-NextPoint;                    //��������
  iIncpid=(sptr->Proportion * iError)                 //E[k]��
              -(sptr->Integral * sptr->LastError)     //E[k-1]��
              +(sptr->Derivative * sptr->PrevError);  //E[k-2]��
              
  sptr->PrevError=sptr->LastError;                    //�洢�������´μ���
  sptr->LastError=iError;
  return(iIncpid);                                    //��������ֵ
}

extern u8  TIM4CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ	
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
  TIM3_PWM_Init(4799,0);//ͨ�ö�ʱ������Ƶʱ��Ƶ��72000000��PWMƵ��=72000000/4800=15Khz�Զ�װ��ֵ4799���жϼ���Ƶ��4799+1=4800��
	//��4799��0����ʾ0������4799��ʱ��Ϊ����PWM��������
	TIM4_Encoder_Init(0xffff,72-1);
	LCD_Init();
	KEY_Init();
	DCMOTOR_BRUSH_TIMx_PWM_Init(); 
	IncPIDInit();
	/* ʹ��PWM��� */
  DCMOTOR_25GA370_Contrl(4,0,0); 
	

	while(1)
	{
		lcdspeed();
		drawspeed();
		para=IncPIDCalc(temp);
	  /* ����������ֵ������ǰ����ٶ� */
		//if((para<-3)||(para>3)) // ���� PID ��������������СʱƵ�����������𵴡�
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

