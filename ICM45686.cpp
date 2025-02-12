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

//WHO_AM_Iの判定
uint8_t ICM45686::verify_connection(){

	uint8_t product_id = 0x00;
	uint8_t error_count = 0;

	//0xE9なら成功
	while(product_id != 0xE9){

		ICM45686_HAL::read(ICM45686_HAL::REGISTER::WHO_AM_I, &product_id, 1);
		error_count ++;

		if(error_count >= 100){

			////////WHO_AM_I 失敗時の処理//////////
			while(1){


			}
			/////////////////////////////////////
		}
	}

	return 0;
}

//加速度センサーの設定
uint8_t ICM45686::accel_mode(ICM45686::mode mode, ICM45686::accel_scale scale, ICM45686::odr odr){

	//現在の値を取得
	uint8_t mode_temp = 0x00;
	ICM45686::read(ICM45686_HAL::REGISTER::PWR_MGMT0, &mode_temp, 1);

	//加速度センサーの電源モードの設定を上書きして書き込み
	uint8_t command = mode_temp |= (uint8_t)mode;
	ICM45686::write(ICM45686::REGISTER::PWR_MGMT0, &command, 1);

	//ODRとscaleを書き込み
	command = (uint8_t)odr + (((uint8_t)scale) << 4);
	ICM45686::write(ICM45686::REGISTER::ACCEL_CONFIG, &command, 1);


	return 0;
}

//ジャイロセンサーの設定
uint8_t ICM45686::gyro_mode(ICM45686::mode mode, ICM45686::gyro_scale scale,  ICM45686::odr odr){

	//現在の値を取得
	uint8_t mode_temp = 0x00;
	ICM45686::read(ICM45686_HAL::REGISTER::PWR_MGMT0, &mode_temp, 1);

	//ジャイロセンサーの電源モードの設定を上書きして書き込み
	uint8_t command = mode_temp |= (uint8_t)mode << 2;
	ICM45686::write(ICM45686::REGISTER::PWR_MGMT0, &command, 1);

	//ODRとscaleを書き込み
	command = (uint8_t)odr + ((uint8_t)scale << 4);
	ICM45686::write(ICM45686::REGISTER::GYRO_CONFIG, &command, 1);

	return 0;
}

//値の取得
uint8_t ICM45686::get_data(int16_t accel_data[3], int16_t gyro_data[3]){

	ICM45686::read(ICM45686_HAL::REGISTER::ACCEL_DATA_X1_UI, raw_data, 12);

	//取得成功
	if(raw_data[1] != 0 && raw_data[3] != 3 && raw_data[5] != 0){

		accel_data[0]  = (int16_t)(raw_data[0] | raw_data[1] << 8);
		accel_data[1]  = (int16_t)(raw_data[2] | raw_data[3] << 8);
		accel_data[2]  = (int16_t)(raw_data[4] | raw_data[5] << 8);

		gyro_data[0]  = (int16_t)(raw_data[6]  | raw_data[7] << 8);
		gyro_data[1]  = (int16_t)(raw_data[8]  | raw_data[9] << 8);
		gyro_data[2]  = (int16_t)(raw_data[10] | raw_data[11] << 8);

		//バッファーのクリア
		for(uint8_t i=0; i<12; i++){

			raw_data[i] = 0;
		}
	}
	//取得失敗
	else{

		return 1;
	}
	return 0;
}
