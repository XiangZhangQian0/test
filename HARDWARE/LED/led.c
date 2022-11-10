#include "led.h"
#include "User.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ��ӢSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //���-->PE.10 �˿�����
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_SetBits(GPIOE,GPIO_Pin_10); 						 //PE.10 ����� 

	/* =*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //������-->PB.8 �˿�����
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_SetBits(GPIOB,GPIO_Pin_8); 
}
/*LED״̬*/
void LED_Start(u8 Mode)
{
	if (1 == Mode) {//�����˸-----��ʾȱˮ
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			LED0 = !LED0;
		}
	}
	else if (2 == Mode) {//�̵���˸-----��ʾ��ˮ��ˮ��Ҫ��������
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			LED1 = !LED1;			
		}
		LED0 = 1;
	}
	else if (3 == Mode) {//�������˸
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			LED0 = !LED0;
			LED1 = !LED1;
			MOTOR = 1;
		}
	}
	else if (4 == Mode) {//��ƺ��̵Ƴ�����---��ʾ������裨�����ʾ����˸��
		LED0 = 0;
		LED1 = 0;
		if (User.Run_Time_ms >= 500) {
			User.Run_Time_ms = 0;
			MOTOR = !MOTOR;
		}
	}	
}


