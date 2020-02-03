#include "main.h"


#define MAX_DRIVERS_NUMBER 1

#define START_STEPS_NUMBER 5


typedef struct{
	GPIO_TypeDef * GPIO_Port;
	uint16_t nEN, MS1, MS2, MS3, nRST, nSLEEP, STEP, DIR;
	TIM_HandleTypeDef Timer;
	uint8_t Index, DriverDisable;
	
}HR4988_DriverTypeDef;

typedef enum step_enum{
	STEP_FULL=0x00U,
	STEP_1_2=0x04U,
	STEP_1_4=0x02U,
	STEP_1_8=0x06U,
	STEP_1_16=0x07U,
	STEP_1_32=0x05U,
	STEP_1_64=0x03U,
	STEP_1_128=0x01U	
}HR4988_StepMode;

typedef enum dir_enum{
	CW_DIR=0x00U,
	CCW_DIR
	
}HR4988_Direction;

void HR4988_DriverReset(HR4988_DriverTypeDef * DriverStruct);

void HR4988_SetStepMode(HR4988_DriverTypeDef * DriverStruct,HR4988_StepMode Mode);

void HR4988_DriverInit(HR4988_DriverTypeDef * DriverStruct);

void HR4988_RunMotor(HR4988_DriverTypeDef * DriverStruct,HR4988_Direction Dir);

void HR4988_StopMotor(HR4988_DriverTypeDef * DriverStruct);

void HR4988_RunFixedSteps(HR4988_DriverTypeDef *DriverStruct, uint64_t Stepcount, HR4988_Direction Dir);
