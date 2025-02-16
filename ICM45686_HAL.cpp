/*
 * ICM45686_HAL.cpp
 *
 *  Created on: Dec 17, 2024
 *      Author: aoi25
 */

#include <ICM45686_HAL.h>

ICM45686_HAL::ICM45686_HAL(I2C_HandleTypeDef *Pin_Data){

	//使用するピンの情報を受け取る
	I2C_Pin = Pin_Data;

}

void ICM45686_HAL::Write(ICM45686_HAL::REGISTER REGISTER_ADDR, uint8_t* Command, uint8_t Len){

	HAL_I2C_Mem_Write(I2C_Pin, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, Command, Len, 1);
}

void ICM45686_HAL::Read(ICM45686_HAL::REGISTER REGISTER_ADDR, uint8_t* Receive_Buffer, uint8_t Len){

	HAL_I2C_Mem_Read(I2C_Pin, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, Receive_Buffer, Len, 1);
}
