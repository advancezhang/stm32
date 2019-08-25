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
#include "remote.h"
#include "main.h"

enum eStaSystem staSystem = E_NORMAL;  //系统运行状态

typedef struct 
{
   __IO int      SetPoint;                                 //设定目标 Desired Value
   __IO double   Proportion;                               //比例常数 Proportional Const
   __IO double   Integral;                                 //积分常数 Integral Const
   __IO double   Derivative;                               //微分常数 Derivative Const
   __IO int      LastError;                                //Error[-1]
   __IO int      PrevError;                                //Error[-2]
}PID;


float P_DATA=1.5;                               //P参数
float I_DATA=3.8;                                //I参数
float D_DATA=6.4;                               //D参数

uint16_t dcmotor_speed=3000;
double encoder_speed=0;
u16 count=37;

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
extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值	

u16 adcx;
float temp;
float para;
float cnt;
u8 key;

u8 i=0;
u8 d=0;
u8 A=0;
u8 S=0;
u8 p=0;
u8 switchP=0;
u8 switchI=0;
u8 switchD=0;
u8 switchspeed=0;
u8 switchangle=0;
u8 Break=0;

void lcdspeed(void)
{
  u8 buffer[3];
	if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
	{
		cnt=TIM5CH1_CAPTURE_STA&0X3F;
		cnt*=65536;//溢出时间总和
		cnt+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间
		cnt=1000000/(cnt*334);
		TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
	}
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
	dcmotor_speed +=para;  
	if(dcmotor_speed>60000)dcmotor_speed=0;      
	DCMOTOR_25GA370_Contrl(1,1,dcmotor_speed);
}
void drawspeed(void)
{
	u8 set;
	u8 a;
	count+=10;
	LCD_DrawLine(count,450-temp*2,count+10,450-temp*2);
	if(count>450)
	{
		count=37;
		LCD_Fill(47,212,468,448,WHITE);
	}
	for(set=0;set<=10;set++)
	{
		LCD_DrawLine(45,set*20+230,33,set*20+230);
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
	#define SIZE0 sizeof(str)
	u16 seat; 
  u8 uart=0;	
	u16 len;	
	u8 str[15];
	u8 speed[4];
	u8 ptr[4];
	u8 itr[4];
	u8 dtr[4];
	u8 datatemp0[SIZE0];
	if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(seat=0;seat<len;seat++)
			{
				USART_SendData(USART1, USART_RX_BUF[seat]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET)//等待发送结束
				{
					uart=1;
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
		if(uart)
		{
			AT24CXX_Write(0,(u8*)str,SIZE0);
		}
		AT24CXX_Read(0,datatemp0,18);
		speed[0]=datatemp0[0];
		speed[1]=datatemp0[1];
		speed[2]=datatemp0[2];
		 
		ptr[0]=datatemp0[4];
		ptr[1]=datatemp0[5];
		ptr[2]=datatemp0[6];
		 
		itr[0]=datatemp0[8];
		itr[1]=datatemp0[9];
		itr[2]=datatemp0[10];
		 
		dtr[0]=datatemp0[12];
		dtr[1]=datatemp0[13];
		dtr[2]=datatemp0[14];
		sptr->SetPoint=atoi((char*)speed);
		LCD_ShowString(95,160,45,40,24,speed);
		sptr->Proportion=atoi((char*)ptr);
		LCD_ShowString(92,720,37,40,24,ptr);
		sptr->Integral=atoi((char*)itr);
		LCD_ShowString(246,720,37,40,24,itr);
		sptr->Derivative=atoi((char*)dtr);
		LCD_ShowString(400,720,37,40,24,dtr);
}
void scan(void)
{
	key=Remote_Scan();	
		if(key)
		{	  
			switch(key)
			{
				case 98:
					switchP=1;
				  switchI=0;
				  switchD=0;
				  switchspeed=0;
				  switchangle=0;
				  p=0;break;
				case 34:
					switchP=0;
				  switchI=1;
				  switchD=0;
				  switchspeed=0;
				  switchangle=0;
				  i=0;break;
				case 194:
				  switchP=0;
				  switchI=0;
				  switchD=1;
				  switchspeed=0;
				  switchangle=0;
				  d=0;break;
				case 2:
					switchP=0;
				  switchI=0;
				  switchD=0;
				  switchspeed=1;
				  switchangle=0;
				  S=0;break;
				case 168:
					switchP=0;
				  switchI=0;
				  switchD=0;
				  switchspeed=0;
				  switchangle=1;
				  A=0;break;
				case 162:
					switchP=0;
				  switchI=0;
				  switchD=0;
				  switchspeed=0;
				  switchangle=0;
				  Break=1;break;
				case 226:
					Break=0;LCD_Fill(0,0,475,790,WHITE);break;
			}
		}
}
void ScanAll(void)
{
	controlP();
	controlI();
	controlD();
	controlSpeed();
	controlAngle();
}
void controlP(void)
{
	u8 Pis[255];
//	#define SIZE1 sizeof(Pis)
//	u8 datatemp1[SIZE1];
	key=Remote_Scan();
	if(switchP)
	{
		if(key)
		{	  
			switch(key)
			{
				case 104:Pis[p] = '1';Pis[p+1] = '\0';p+=1;break;
				case 152:Pis[p] = '2';Pis[p+1] = '\0';p+=1;break;
				case 176:Pis[p] = '3';Pis[p+1] = '\0';p+=1;break;
				case 48:Pis[p] = '4';Pis[p+1] = '\0';p+=1;break;
				case 24:Pis[p] = '5';Pis[p+1] = '\0';p+=1;break;
				case 122:Pis[p] = '6';Pis[p+1] = '\0';p+=1;break;
				case 16:Pis[p] = '7';Pis[p+1] = '\0';p+=1;break;
				case 56:Pis[p] = '8';Pis[p+1] = '\0';p+=1;break;
				case 90:Pis[p] = '9';Pis[p+1] = '\0';p+=1;break;
				case 66:Pis[p] = '0';Pis[p+1] = '\0';p+=1;break;
				case 82:Pis[p] = '.';Pis[p+1] = '\0';p+=1;break;
				
			}
		while(p>=3)
		{
			p=0;
		}
		sptr->Proportion=atoi((char*)Pis);
		LCD_ShowString(15,750,37,40,24,"P");
		LCD_ShowString(92,720,37,40,24,Pis);
		}
	}
//	if(Break)
//  {
//	  AT24CXX_Write(273,(u8*)Pis,SIZE1);
//  }
//	AT24CXX_Read(273,datatemp1,255);
//	LCD_ShowString(92,720,37,40,24,datatemp1);
	
}
void controlI(void)
{
	u8 Iis[255];
//	#define SIZE2 sizeof(Iis)
//	u8 datatemp2[SIZE2];
	key=Remote_Scan();
	if(switchI)
	{
		if(key)
		{	  
			switch(key)
			{
				case 104:Iis[i] = '1';Iis[i+1] = '\0';i+=1;break;
				case 152:Iis[i] = '2';Iis[i+1] = '\0';i+=1;break;
				case 176:Iis[i] = '3';Iis[i+1] = '\0';i+=1;break;
				case 48:Iis[i] = '4';Iis[i+1] = '\0';i+=1;break;
				case 24:Iis[i] = '5';Iis[i+1] = '\0';i+=1;break;
				case 122:Iis[i] = '6';Iis[i+1] = '\0';i+=1;break;
				case 16:Iis[i] = '7';Iis[i+1] = '\0';i+=1;break;
				case 56:Iis[i] = '8';Iis[i+1] = '\0';i+=1;break;
				case 90:Iis[i] = '9';Iis[i+1] = '\0';i+=1;break;
				case 66:Iis[i] = '0';Iis[i+1] = '\0';i+=1;break;
				case 82:Iis[i] = '.';Iis[i+1] = '\0';i+=1;break;
			}
			while(i>=3)
			{
				i=0;
			}
			sptr->Integral=atoi((char*)Iis);
			LCD_ShowString(246,720,37,40,24,Iis);
			LCD_ShowString(15,750,37,40,24,"I");
		}
	}
//	if(Break)
//  {
//	  AT24CXX_Write(528,(u8*)Iis,SIZE2);
//  }
//	AT24CXX_Read(528,datatemp2,255);
//	LCD_ShowString(246,720,37,40,24,datatemp2);
}
void controlD(void)
{
	u8 Dis[255];
//	#define SIZE3 sizeof(Dis)
//	u8 datatemp3[SIZE3];
	key=Remote_Scan();
	if(switchD)
	{
		if(key)
		{	  
			switch(key)
			{
				case 104:Dis[d] = '1';Dis[d+1] = '\0';d+=1;break;
				case 152:Dis[d] = '2';Dis[d+1] = '\0';d+=1;break;
				case 176:Dis[d] = '3';Dis[d+1] = '\0';d+=1;break;
				case 48:Dis[d] = '4';Dis[d+1] = '\0';d+=1;break;
				case 24:Dis[d] = '5';Dis[d+1] = '\0';d+=1;break;
				case 122:Dis[d] = '6';Dis[d+1] = '\0';d+=1;break;
				case 16:Dis[d] = '7';Dis[d+1] = '\0';d+=1;break;
				case 56:Dis[d] = '8';Dis[d+1] = '\0';d+=1;break;
				case 90:Dis[d] = '9';Dis[d+1] = '\0';d+=1;break;
				case 66:Dis[d] = '0';Dis[d+1] = '\0';d+=1;break;
				case 82:Dis[d] = '.';Dis[d+1] = '\0';d+=1;break;
			}
			while(d>=3)
			{
				d=0;
			}
			sptr->Derivative=atoi((char*)Dis);
			LCD_ShowString(400,720,37,40,24,Dis);
			LCD_ShowString(15,750,37,40,24,"D");
		}
	}
//	if(Break)
//  {
//	  AT24CXX_Write(3,(u8*)Dis,SIZE3);
//  }
//	AT24CXX_Read(3,datatemp3,255);
//	LCD_ShowString(400,720,37,40,24,datatemp3);
}

void controlSpeed(void)
{
	u8 Sis[255];
//	#define SIZE4 sizeof(Sis)
//	u8 datatemp4[SIZE4];
	key=Remote_Scan();
	if(switchspeed)
	{
		if(key)
		{	  
			switch(key)
			{
				case 104:Sis[S] = '1';Sis[S+1] = '\0';S+=1;break;
				case 152:Sis[S] = '2';Sis[S+1] = '\0';S+=1;break;
				case 176:Sis[S] = '3';Sis[S+1] = '\0';S+=1;break;
				case 48:Sis[S] = '4';Sis[S+1] = '\0';S+=1;break;
				case 24:Sis[S] = '5';Sis[S+1] = '\0';S+=1;break;
				case 122:Sis[S] = '6';Sis[S+1] = '\0';S+=1;break;
				case 16:Sis[S] = '7';Sis[S+1] = '\0';S+=1;break;
				case 56:Sis[S] = '8';Sis[S+1] = '\0';S+=1;break;
				case 90:Sis[S] = '9';Sis[S+1] = '\0';S+=1;break;
				case 66:Sis[S] = '0';Sis[S+1] = '\0';S+=1;break;
				case 82:Sis[S] = '.';Sis[S+1] = '\0';S+=1;break;
			}
			while(S>=3)
			{
				S=0;
			}
			sptr->SetPoint=atoi((char*)Sis);
			LCD_ShowString(95,160,45,40,24,Sis);
			LCD_ShowString(15,750,37,40,24,"S");
		}
	}
//	if(Break)
//  {
//	  AT24CXX_Write(4,(u8*)Sis,SIZE4);
//  }
//	AT24CXX_Read(4,datatemp4,255);
//	LCD_ShowString(95,160,45,40,24,datatemp4);
}
void controlAngle(void)
{
	u8 Ais[255];
//	#define SIZE5 sizeof(Ais)
//	u8 datatemp5[SIZE5];
	key=Remote_Scan();
	if(switchangle)
	{
		if(key)
		{	  
			switch(key)
			{
				case 104:Ais[A] = '1';Ais[A+1] = '\0';A+=1;break;
				case 152:Ais[A] = '2';Ais[A+1] = '\0';A+=1;break;
				case 176:Ais[A] = '3';Ais[A+1] = '\0';A+=1;break;
				case 48:Ais[A] = '4';Ais[A+1] = '\0';A+=1;break;
				case 24:Ais[A] = '5';Ais[A+1] = '\0';A+=1;break;
				case 122:Ais[A] = '6';Ais[A+1] = '\0';A+=1;break;
				case 16:Ais[A] = '7';Ais[A+1] = '\0';A+=1;break;
				case 56:Ais[A] = '8';Ais[A+1] = '\0';A+=1;break;
				case 90:Ais[A] = '9';Ais[A+1] = '\0';A+=1;break;
				case 66:Ais[A] = '0';Ais[A+1] = '\0';A+=1;break;
				case 82:Ais[A] = '.';Ais[A+1] = '\0';A+=1;break;
			}
			while(A>=3)
			{
				A=0;
			}
			LCD_ShowString(325,160,45,40,24,Ais);
		  LCD_ShowString(15,750,37,40,24,"A");
		}
	}
//	if(Break)
//  {
//	  AT24CXX_Write(5,(u8*)Ais,SIZE5);
//  }
//	AT24CXX_Read(5,datatemp5,255);
//	LCD_ShowString(325,160,45,40,24,datatemp5);
}
