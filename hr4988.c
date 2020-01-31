#include "hr4988.h"

HR4988_DriverTypeDef ActiveDriversArr[MAX_DRIVERS_NUMBER];
uint64_t DriverSteps[MAX_DRIVERS_NUMBER];
uint8_t active_drivers;

void HR4988_DriverReset(HR4988_DriverTypeDef * DriverStruct){
	
	HAL_TIM_Base_Stop_IT(&DriverStruct->StartFreqTimer);
	HAL_TIM_Base_Stop_IT(&DriverStruct->NormalFreqTimer);
	
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->nEN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->nRST,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->nSLEEP,GPIO_PIN_RESET);
	
	HAL_Delay(10);
	
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->nRST,GPIO_PIN_SET);
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->nSLEEP,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->DIR,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->MS1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->MS2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->MS3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->STEP,GPIO_PIN_RESET);
}

void HR4988_SetStepMode(HR4988_DriverTypeDef * DriverStruct,HR4988_StepMode Mode){
	
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->MS1,(GPIO_PinState)(Mode & (1<<2)));
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->MS2,(GPIO_PinState)(Mode & (1<<1)));
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->MS3,(GPIO_PinState)(Mode & (1<<0)));
	
}

void HR4988_SetStepFreq(TIM_HandleTypeDef HalTimerHandle){
	
}

void HR4988_RunMotor(HR4988_DriverTypeDef * DriverStruct,HR4988_Direction Dir){
	
	HAL_GPIO_WritePin(DriverStruct->GPIO_Port,DriverStruct->nEN,GPIO_PIN_RESET);
	
	HAL_TIM_Base_Start_IT(&DriverStruct->StartFreqTimer);
	
		
}

uint8_t HR4988_DriversInit(HR4988_DriverTypeDef * Drivers,uint8_t DriverNumber){
	
	uint8_t err_flag;
	if (DriverNumber>MAX_DRIVERS_NUMBER){
		
		err_flag=0xFFU;
	
	}
	else{
		active_drivers=DriverNumber;
		
		for (uint8_t i=0;i<DriverNumber;i++){
		
			HR4988_DriverReset(&Drivers[i]);
			ActiveDriversArr[i]=Drivers[i];
			
		}
		
		err_flag=0x00U;
	
	}
	
	return err_flag;		
		
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	for (uint8_t i=0;i<active_drivers;i++){
		
		if(htim->Instance==ActiveDriversArr[i].StartFreqTimer.Instance){
			HAL_GPIO_TogglePin(ActiveDriversArr[i].GPIO_Port,ActiveDriversArr[i].STEP);
			
		}
	}

  
}
