#include "led.h"
#include "User.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK 精英STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //电机-->PE.10 端口配置
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_SetBits(GPIOE,GPIO_Pin_10); 						 //PE.10 输出高 

	/* =*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //蜂鸣器-->PB.8 端口配置
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_SetBits(GPIOB,GPIO_Pin_8); 
}
/*LED状态*/
void LED_Start(u8 Mode)
{
	if (1 == Mode) {//红灯闪烁-----表示缺水
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			LED0 = !LED0;
		}
	}
	else if (2 == Mode) {//绿灯闪烁-----表示加水，水快要满出来了
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			LED1 = !LED1;			
		}
		LED0 = 1;
	}
	else if (3 == Mode) {//跑马灯闪烁
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			LED0 = !LED0;
			LED1 = !LED1;
			MOTOR = 1;
		}
	}
	else if (4 == Mode) {//红灯和绿灯常亮，---表示电机搅拌（电机提示灯闪烁）
		LED0 = 0;
		LED1 = 0;
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			MOTOR = !MOTOR;
		}
	}	
}


