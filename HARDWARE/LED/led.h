#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 		PBout(5)// PB5
#define LED1 		PEout(5)// PE5	
#define MOTOR  		PEout(10)// PD3	���
#define BEEP  		PBout(8)// PD3	������
#define LED_ON	0
#define LED_OFF	1
void LED_Init(void);//��ʼ��
void LED_Start(u8 Mode);

		 				    
#endif
