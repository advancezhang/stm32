#include "delay.h"
#include "usart.h"
#include "encoder.h"
//#include "timer.h"
#include "key.h"
#include "lcd.h"
#include "stdio.h"
#include "brush.h" 
#include "24cxx.h"
#include "usmart.h"	 
#include "24cxx.h"
#include "show.h"

typedef struct 
{
   __IO int      SetPoint;                                 //设定目标 Desired Value
   __IO double   Proportion;                               //比例常数 Proportional Const
   __IO double   Integral;                                 //积分常数 Integral Const
   __IO double   Derivative;                               //微分常数 Derivative Const
   __IO int      LastError;                                //Error[-1]
   __IO int      PrevError;                                //Error[-2]
}PID;


float P_DATA=0.5;                               //P参数
float I_DATA=0.8;                                //I参数
float D_DATA=0.4;                               //D参数

uint16_t dcmotor_speed=3000;
double encoder_speed=0;
u16 count=47;

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
              -(sptr->Derivative * sptr->PrevError);  //E[k-2]项
              
  sptr->PrevError=sptr->LastError;                    //存储误差，用于下次计算
  sptr->LastError=iError;
  return(iIncpid);                                    //返回增量值
}

u16 adcx;
float temp;
float para;

void lcdspeed(void)
{
  u8 buffer[3];
	adcx=TIM5->CNT;
	temp=(float)adcx*0.7;
	if(temp>2000)
	{
		temp=65535*0.7-temp;
		sprintf((char*)buffer,"%.2f",temp);
	  LCD_ShowString(95,35,85,40,24,buffer);
	}
	else
	{
		sprintf((char*)buffer,"%.2f",temp);
		LCD_ShowString(95,35,85,40,24,buffer);
	}
	TIM5->CNT=0;
	para=IncPIDCalc(temp);
	/* 根据增量数值调整当前电机速度 */
	//if((para<-3)||(para>3)) // 不做 PID 调整，避免误差较小时频繁调节引起震荡。
	//{
		dcmotor_speed +=para;  
	//}
	if(dcmotor_speed>60000)dcmotor_speed=0;      
	DCMOTOR_25GA370_Contrl(1,1,dcmotor_speed);
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
	LCD_ShowString(15,720,37,40,24,"KP");
	LCD_ShowString(169,720,37,40,24,"KI");
	LCD_ShowString(323,720,37,40,24,"KD");
	LCD_DrawRectangle(10,10,470,100);
	LCD_DrawRectangle(10,110,470,200);
	LCD_DrawRectangle(45,210,470,450);
	LCD_DrawRectangle(45,470,470,680);
	LCD_DrawRectangle(10,700,470,790);
	LCD_DrawLine(87,700,87,790);
	LCD_DrawLine(164,700,164,790);
	LCD_DrawLine(241,700,241,790);
	LCD_DrawLine(318,700,318,790);
	LCD_DrawLine(395,700,395,790);
	LCD_DrawLine(90,10,90,100);
	LCD_DrawLine(240,10,240,100);
	LCD_DrawLine(320,10,320,100);
	LCD_DrawLine(90,110,90,200);
	LCD_DrawLine(240,110,240,200);
	LCD_DrawLine(320,110,320,200);
}
void USART(void)
{
	#define SIZE1 sizeof(str)
//	#define SIZE2 sizeof(ptr)
//	#define SIZE3 sizeof(itr)
//	#define SIZE4 sizeof(dtr)
	u16 t; 
  u8 key=0;	
	u16 len;	
	u8 str[15];
	u8 speed[4];
	u8 ptr[4];
	u8 itr[4];
	u8 dtr[4];
	u8 datatemp1[SIZE1];
//	u8 datatemp2[SIZE2];
//	u8 datatemp3[SIZE3];
//	u8 datatemp4[SIZE4];
	if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET)//等待发送结束
				{
					key=1;
				}
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}
		str[0]=USART_RX_BUF[0];
		str[1]=USART_RX_BUF[1];
		str[2]=USART_RX_BUF[2];
		str[3]=USART_RX_BUF[3];
		str[4]=USART_RX_BUF[4];
		str[5]=USART_RX_BUF[5];
		str[6]=USART_RX_BUF[6];
		str[7]=USART_RX_BUF[7];
		str[8]=USART_RX_BUF[8];
		str[9]=USART_RX_BUF[9];
		str[10]=USART_RX_BUF[10];
		str[11]=USART_RX_BUF[11];
		str[12]=USART_RX_BUF[12];
		str[13]=USART_RX_BUF[13];
		str[14]=USART_RX_BUF[14];
//		ptr[0]=USART_RX_BUF[3];
//		ptr[1]=USART_RX_BUF[4];
//		ptr[2]=USART_RX_BUF[5];
//		itr[0]=USART_RX_BUF[6];
//		itr[1]=USART_RX_BUF[7];
//		itr[2]=USART_RX_BUF[8];
//		dtr[0]=USART_RX_BUF[9];
//		dtr[1]=USART_RX_BUF[10];
//		dtr[2]=USART_RX_BUF[11];
	  //LCD_ShowString(95,160,45,40,24,str);
//		LCD_ShowString(92,720,77,40,24,ptr);
//   	LCD_ShowString(246,720,77,40,24,itr);
//  	LCD_ShowString(400,720,77,40,24,dtr);
//		printf("num=%d",sptr->SetPoint);
//		printf("\r\n\r\n");
//		if(USART_RX_STA)
//		{
    // key=KEY_Scan(0);
		 if(key)
		 {
		   AT24CXX_Write(0,(u8*)str,SIZE1);
//			AT24CXX_Write(0x00,(u8*)ptr,SIZE2);
//			AT24CXX_Write(0x00,(u8*)itr,SIZE3);
//			AT24CXX_Write(0x00,(u8*)dtr,SIZE4);
	//	}
		 }
		   AT24CXX_Read(0,datatemp1,18);
		
//		AT24CXX_Read(0x00,datatemp2,2);
//		AT24CXX_Read(0x00,datatemp3,2);
//		AT24CXX_Read(0x00,datatemp4,2);
		speed[0]=datatemp1[0];
		speed[1]=datatemp1[1];
		speed[2]=datatemp1[2];
		 
		ptr[0]=datatemp1[4];
		ptr[1]=datatemp1[5];
		ptr[2]=datatemp1[6];
		 
		itr[0]=datatemp1[8];
		itr[1]=datatemp1[9];
		itr[2]=datatemp1[10];
		 
		dtr[0]=datatemp1[12];
		dtr[1]=datatemp1[13];
		dtr[2]=datatemp1[14];
		sptr->SetPoint=atoi((char*)speed);
		LCD_ShowString(95,160,45,40,24,speed);
		sptr->Proportion=atoi((char*)ptr);
		LCD_ShowString(92,720,37,40,24,ptr);
		sptr->Integral=atoi((char*)itr);
		LCD_ShowString(246,720,37,40,24,itr);
		sptr->Derivative=atoi((char*)dtr);
		LCD_ShowString(400,720,37,40,24,dtr);
}

