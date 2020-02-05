#include "main.h"


#define MAX_DRIVERS_NUMBER 1




typedef struct{
	GPIO_TypeDef * GPIO_Port;
	uint16_t EN, STEP, DIR;
	TIM_HandleTypeDef Timer;
	uint8_t Index, DriverDisable, PeriodStep;
	uint16_t StartCounterPeriod, StopCounterPeriod;
	
}HR4988_DriverTypeDef;



typedef enum dir_enum{
	CW_DIR=0x00U,
	CCW_DIR
	
}HR4988_Direction;

void HR4988_DriverReset(HR4988_DriverTypeDef * DriverStruct);



void HR4988_DriverInit(HR4988_DriverTypeDef * DriverStruct);

void HR4988_RunMotor(HR4988_DriverTypeDef * DriverStruct,HR4988_Direction Dir);

void HR4988_StopMotor(HR4988_DriverTypeDef * DriverStruct);

void HR4988_RunFixedSteps(HR4988_DriverTypeDef *DriverStruct, uint64_t Stepcount, HR4988_Direction Dir);
