#include "User.h"
#include "led.h"
#include "timer.h"
#include "key.h"

_un_LED LED = {0};
_User_Data User ={0};

u8 g_Water_State_Flag = 0;//1�������0��ȱˮ

void User_Time(void)
{
	User.Run_Time_ms++;
	User.Run_Time++;
}
/*�ϵ�״̬*/
void User_Start(void)
{
	User.Mode = HYDROPENIA_STEP;
}
/*ȱˮ״̬*/
void User_Hydropenia(void)/*KEY0--��ˮ��ť*/
{
	BEEP = 1;//����
	LED0 = 0;//���
	LED1 = 1;
	g_Water_State_Flag = 0;//ȱˮ
	if (KEY0_PRES == KEY_Scan(0)) {/*�����ˮ��----�����ˮ/��ˮ״̬*/
		User.Run_Time = 0;
		User.Run_Time_ms = 0;
		BEEP = 0;//�رձ���
		LED0 = 1;
		LED1 = 0;
		User.Mode = WATER_STEP;
	}
}
/*��ˮ/��ˮ״̬*/
void User_Water()
{					//��ʾ����->�̡���ˮ
	LED_Start(3);	//��ʾ����->�족��ˮ
	
	if(User.Run_Time >= 1000) {
		BEEP = 0;//�رս�����ɵ���ʾ��
	}
	
	if (User.Run_Time >= 30000) {//30s
		User.Run_Time = 0;
		if (!g_Water_State_Flag) {//��ȱˮ�������30s����
			User.Mode = OVERFLOW_STEP;//�������״̬������ʾ
		}
		else {
			User.Mode = HYDROPENIA_STEP;//ȱˮ
		}
	}
}
/*����״̬*/
void User_Overflow(void)/*KEY1--���谴ť*/
{
	BEEP = 1;
	LED0 = 1;
	LED1 = 0;
	if ((KEY0_PRES == KEY_Scan(0))) {/*�ֶ��������״̬*/
		User.Run_Time_ms = 0;
		User.Run_Time = 0;
		BEEP = 0;
		User.Mode = STIR_STEP;/*���----�������״̬*/
	}
}
/*����״̬*/
void User_Stir(void)
{
	LED_Start(4);//-��ʾ�������
	
	if (User.Run_Time >= 60000) {//1min
		User.Run_Time_ms = 0;
		User.Run_Time = 0;
		User.Mode = WATER_STEP;/*��ˮ״̬*/
		g_Water_State_Flag = 1;
		LED0 = 0;
		LED1 = 1;
		BEEP = 1;//��ʾ��
	}
}


void User_Run(void)
{
	switch (User.Mode)
    {
		case START_STEP:			//�ϵ�״̬
            
			User_Start();
		break;
		
		case HYDROPENIA_STEP:		//ȱˮ
		
			User_Hydropenia();
		break;
#if(1)		
		case OVERFLOW_STEP:			//���
		
			User_Overflow();
		break;
		
		case STIR_STEP:				//����
		
			User_Stir();
		break;
		
		case WATER_STEP:			//��ˮ����ˮ
		
			User_Water();
		break;
		#endif
	}
}




