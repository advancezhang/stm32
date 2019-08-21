#include "encoder.h"

TIM_ICInitTypeDef TIM_ICInitStructure;
void TIM5_Encoder_Init(u16 arr,u16 psc)            ///TIM4 编码器输入，TIM4_CH1作A相，TIM4_CH2作B相GPIO_Pin_6|GPIO_Pin_7;
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);// 使能定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//io口使能使用到的捕获编码器AB相借
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//浮空输入	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 //推挽输出 ，IO口速度为50MHz
 //初始化TIM4的时机单元	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
              //配置对应寄存器为编码器接口模式以及配置相关的输入捕获配置
             //THE MODE OF ENCODER 
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;		 //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM_ICInitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM5, TIM_FLAG_Update);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM5,0);
  TIM_Cmd(TIM5, ENABLE); //使能TIM4 
}
u8 TIM5CH1_CAPTURE_STA=0;		//输入捕获状态		
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
 //定时器4中断服务程序	
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}
float HF_Get_Encode_TIM5(void)
{
	float cnt;
  cnt = (float)((uint16_t)0x7fff) - (float)((uint16_t)(TIM5->CNT)) ;
  TIM5->CNT = 0x7fff;
  return cnt;
}

