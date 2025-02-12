/*
 * ICM45686_HAL.cpp
 *
 *  Created on: Dec 17, 2024
 *      Author: aoi25
 */

#include <ICM45686_HAL.h>

ICM45686_HAL::ICM45686_HAL(I2C_HandleTypeDef *use_i2cPin){

	//使用するピンの情報を受け取る
	i2c_pin = use_i2cPin;

}

void ICM45686_HAL::write(ICM45686_HAL::REGISTER REGISTER_ADDR, uint8_t* command, uint8_t len){

	HAL_I2C_Mem_Write(i2c_pin, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, command, len, 1000);
}

void ICM45686_HAL::read(ICM45686_HAL::REGISTER REGISTER_ADDR, uint8_t* receive_buffer, uint8_t len){

	HAL_I2C_Mem_Read(i2c_pin, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, receive_buffer, len, 1000);
}
