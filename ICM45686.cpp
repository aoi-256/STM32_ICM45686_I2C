/*
 * ICM45686.cpp
 *
 *  Created on: Dec 17, 2024
 *      Author: aoi25
 */

#include <ICM45686.h>
#include <bitset>

ICM45686::ICM45686(I2C_HandleTypeDef* I2C_Pin):ICM45686_HAL(I2C_Pin){


}

//WHO_AM_Iの判定
uint8_t ICM45686::Connection(){

	uint8_t Product_ID = 0x00;
	uint8_t Error = 0;

	//0xE9なら成功
	while(Product_ID != 0xE9){

		ICM45686_HAL::Read(ICM45686_HAL::REGISTER::WHO_AM_I, &Product_ID, 1);
		Error ++;

		if(Error >= 100){

			//WHO_AM_I 失敗
			while(1){


			}
		}
	}

	return 0;
}

//加速度センサーの設定
uint8_t ICM45686::Accel_Config(ICM45686::Mode Mode, ICM45686::Accel_Scale Scale, ICM45686::ODR ODR){

	//現在の値を取得
	uint8_t Now_Mode = 0x00;
	ICM45686::Read(ICM45686_HAL::REGISTER::PWR_MGMT0, &Now_Mode, 1);

	//加速度センサーの電源モードの設定を上書きして書き込み
	uint8_t  Command = Now_Mode |= (uint8_t)Mode;
	ICM45686::Write(ICM45686::REGISTER::PWR_MGMT0, &Command, 1);

	//ODRとscaleを書き込み
	Command = (uint8_t)ODR + (((uint8_t)Scale) << 4);
	ICM45686::Write(ICM45686::REGISTER::ACCEL_CONFIG, &Command, 1);


	return 0;
}

//ジャイロセンサーの設定
uint8_t ICM45686::Gyro_Config(ICM45686::Mode Mode, ICM45686::Gyro_Scale Scale,  ICM45686::ODR ODR){

	//現在の値を取得
	uint8_t Now_Mode = 0x00;
	ICM45686::Read(ICM45686_HAL::REGISTER::PWR_MGMT0, &Now_Mode, 1);

	//ジャイロセンサーの電源モードの設定を上書きして書き込み
	uint8_t Command = Now_Mode |= (uint8_t)Mode << 2;
	ICM45686::Write(ICM45686::REGISTER::PWR_MGMT0, &Command, 1);

	//ODRとscaleを書き込み
	Command = (uint8_t)ODR + ((uint8_t)Scale << 4);
	ICM45686::Write(ICM45686::REGISTER::GYRO_CONFIG, &Command, 1);

	return 0;
}

//値の取得
uint8_t ICM45686::Get_Data(int16_t Accel_Data[3], int16_t Gyro_Data[3]){

	ICM45686::Read(ICM45686_HAL::REGISTER::ACCEL_DATA_X1_UI, Raw_Data, 12);

	Accel_Data[0]  = (int16_t)(Raw_Data[0] | Raw_Data[1] << 8);
	Accel_Data[1]  = (int16_t)(Raw_Data[2] | Raw_Data[3] << 8);
	Accel_Data[2]  = (int16_t)(Raw_Data[4] | Raw_Data[5] << 8);

	Gyro_Data[0]  = (int16_t)(Raw_Data[6]  | Raw_Data[7] << 8);
	Gyro_Data[1]  = (int16_t)(Raw_Data[8]  | Raw_Data[9] << 8);
	Gyro_Data[2]  = (int16_t)(Raw_Data[10] | Raw_Data[11] << 8);

	//バッファーのクリア
	for(uint8_t i=0; i<12; i++){

		Raw_Data[i] = 0;
	}
}
