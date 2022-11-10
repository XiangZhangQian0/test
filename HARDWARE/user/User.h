#ifndef __User_H
#define __User_H


#include "sys.h"


typedef struct
{
	u8
		Flag	:1;
}_st_LED;
typedef union
{
	u8 DATA;
	_st_LED Data;	
} _un_LED;
extern _un_LED LED;




typedef struct 
{
	u8 Mode;
	u16 Run_Time_ms;
	u8 Run_Time_min;
	u8 Run_Time_sec;
	u16 Run_Time;
	u32 LED_Time;
}_User_Data;

extern _User_Data User;
enum
{
	START_STEP = 0,		//上电状态

	HYDROPENIA_STEP,	//缺水
	OVERFLOW_STEP,		//溢出
	STIR_STEP,			//搅拌
	WATER_STEP,			//加水、洒水
};
void User_Time(void);
void User_Init(void);
void User_Run(void);

#endif
