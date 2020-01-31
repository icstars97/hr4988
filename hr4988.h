#include "main.h"

#ifndef MAX_DRIVERS_NUMBER
#define MAX_DRIVERS_NUMBER 1
#endif

#ifndef START_STEPS_NUMBER
#define START_STEPS_NUMBER 5
#endif

typedef struct{
	GPIO_TypeDef * GPIO_Port;
	uint16_t nEN, MS1, MS2, MS3, nRST, nSLEEP, STEP, DIR;
	TIM_HandleTypeDef StartFreqTimer, NormalFreqTimer;
	uint8_t Index;
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
	CCW_dir
	
}HR4988_Direction;

void HR4988_DriverReset(HR4988_DriverTypeDef * DriverStruct);

void HR4988_SetStepMode(HR4988_DriverTypeDef * DriverStruct,HR4988_StepMode Mode);

uint8_t HR4988_DriversInit(HR4988_DriverTypeDef * Drivers,uint8_t DriverNumber);
