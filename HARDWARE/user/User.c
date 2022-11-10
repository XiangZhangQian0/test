#include "User.h"
#include "led.h"
#include "timer.h"
#include "key.h"

_un_LED LED = {0};
_User_Data User ={0};

u8 g_Water_State_Flag = 0;//1：溢出，0：缺水

void User_Time(void)
{
	User.Run_Time_ms++;
	User.Run_Time++;
}
/*上电状态*/
void User_Start(void)
{
	User.Mode = HYDROPENIA_STEP;
}
/*缺水状态*/
void User_Hydropenia(void)/*KEY0--加水按钮*/
{
	BEEP = 1;//报警
	LED0 = 0;//红的
	LED1 = 1;
	g_Water_State_Flag = 0;//缺水
	if (KEY0_PRES == KEY_Scan(0)) {/*点击加水间----进入加水/洒水状态*/
		User.Run_Time = 0;
		User.Run_Time_ms = 0;
		BEEP = 0;//关闭报警
		LED0 = 1;
		LED1 = 0;
		User.Mode = WATER_STEP;
	}
}
/*加水/洒水状态*/
void User_Water()
{					//表示“红->绿”加水
	LED_Start(3);	//表示“绿->红”洒水
	
	if(User.Run_Time >= 1000) {
		BEEP = 0;//关闭搅拌完成的提示音
	}
	
	if (User.Run_Time >= 30000) {//30s
		User.Run_Time = 0;
		if (!g_Water_State_Flag) {//在缺水的情况下30s加满
			User.Mode = OVERFLOW_STEP;//进入加满状态报警提示
		}
		else {
			User.Mode = HYDROPENIA_STEP;//缺水
		}
	}
}
/*加满状态*/
void User_Overflow(void)/*KEY1--搅拌按钮*/
{
	BEEP = 1;
	LED0 = 1;
	LED1 = 0;
	if ((KEY0_PRES == KEY_Scan(0))) {/*手动进入搅拌状态*/
		User.Run_Time_ms = 0;
		User.Run_Time = 0;
		BEEP = 0;
		User.Mode = STIR_STEP;/*点击----进入搅拌状态*/
	}
}
/*搅拌状态*/
void User_Stir(void)
{
	LED_Start(4);//-表示电机搅拌
	
	if (User.Run_Time >= 60000) {//1min
		User.Run_Time_ms = 0;
		User.Run_Time = 0;
		User.Mode = WATER_STEP;/*洒水状态*/
		g_Water_State_Flag = 1;
		LED0 = 0;
		LED1 = 1;
		BEEP = 1;//提示音
	}
}


void User_Run(void)
{
	switch (User.Mode)
    {
		case START_STEP:			//上电状态
            
			User_Start();
		break;
		
		case HYDROPENIA_STEP:		//缺水
		
			User_Hydropenia();
		break;
#if(1)		
		case OVERFLOW_STEP:			//溢出
		
			User_Overflow();
		break;
		
		case STIR_STEP:				//搅拌
		
			User_Stir();
		break;
		
		case WATER_STEP:			//加水、洒水
		
			User_Water();
		break;
		#endif
	}
}




