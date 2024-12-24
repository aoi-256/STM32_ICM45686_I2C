/*
 * ICM45686.cpp
 *
 *  Created on: Dec 17, 2024
 *      Author: aoi25
 */

#include <ICM45686.h>
#include <bitset>

ICM45686::ICM45686(I2C_HandleTypeDef* i2c_pin):ICM45686_HAL(i2c_pin){


}
uint8_t ICM45686::verify_connection(){

	uint8_t product_id = 0x00;
	uint8_t error_count = 0;

	while(product_id != 0x41){

		ICM45686_HAL::read(ICM45686_HAL::REGISTER::WHO_AM_I, &product_id, 1);
		error_count ++;

		if(error_count >= 100){

			while(1){

			}
		}
	}

	return 0;
}

uint8_t ICM45686::accel_mode(ICM45686::mode mode, ICM45686::accel_scale scale, ICM45686::odr odr){

	//現在の値を取得
	uint8_t mode_temp = 0x00;
	ICM45686::read(ICM45686_HAL::REGISTER::PWR_MGMT0, &mode_temp, 1);

	//変更箇所を上書きして書き込み
	uint8_t command = mode_temp |= (uint8_t)mode;
	ICM45686::write(ICM45686::REGISTER::PWR_MGMT0, &command, 1);

	command = (uint8_t)odr + ((uint8_t)scale << 4);
	ICM45686::write(ICM45686::REGISTER::ACCEL_CONFIG, &command, 1);

	return 0;
}

uint8_t ICM45686::gyro_mode(ICM45686::mode mode, ICM45686::gyro_scale scale,  ICM45686::odr odr){

	//現在の値を取得
	uint8_t mode_temp = 0x00;
	ICM45686::read(ICM45686_HAL::REGISTER::PWR_MGMT0, &mode_temp, 1);

	//変更箇所を上書きして書き込み
	uint8_t command = mode_temp |= (uint8_t)mode << 2;
	ICM45686::write(ICM45686::REGISTER::PWR_MGMT0, &command, 1);

	command = (uint8_t)odr + ((uint8_t)scale << 4);
	ICM45686::write(ICM45686::REGISTER::GYRO_CONFIG, &command, 1);


	return 0;
}

uint8_t ICM45686::get_data(int16_t accel_data[3], int16_t gyro_data[3]){

	ICM45686::read(ICM45686_HAL::REGISTER::ACCEL_DATA_X1_UI, raw_data, 1);

	if(raw_data[1] != 0 && raw_data[3] != 3 && raw_data[5] != 0){

		accel_data[0]  = (int16_t)(raw_data[1] | raw_data[0] << 8);
		accel_data[1]  = (int16_t)(raw_data[3] | raw_data[2] << 8);
		accel_data[2]  = (int16_t)(raw_data[5] | raw_data[4] << 8);

		gyro_data[0]  = (int16_t)(raw_data[7]  | raw_data[6] << 8);
		gyro_data[1]  = (int16_t)(raw_data[9]  | raw_data[8] << 8);
		gyro_data[2]  = (int16_t)(raw_data[11] | raw_data[10] << 8);
	}
	return 0;
}
