/*
 * ICM45686_HAL.h
 *
 *  Created on: Dec 17, 2024
 *      Author: aoi25
 */

#ifndef INC_ICM45686_HAL_H_
#define INC_ICM45686_HAL_H_

#include <cstdint>
#include <i2c.h>

class ICM45686_HAL {

	public:

		enum class REGISTER: uint8_t{

			ACCEL_DATA_X1_UI = 0x00,
			PWR_MGMT0        = 0x10,
			ACCEL_CONFIG     = 0x1B,
			GYRO_CONFIG 	 = 0x1C,
			WHO_AM_I   		 = 0x72
		};

		ICM45686_HAL(I2C_HandleTypeDef* i2c_pin);

		void write(ICM45686_HAL::REGISTER, uint8_t* command, uint8_t len);
		void read(ICM45686_HAL::REGISTER, uint8_t* receive_buffer, uint8_t len);

	private:

		uint8_t I2C_ADDR = 0b1101000 << 1;
		I2C_HandleTypeDef* i2c_pin;
};

#endif /* INC_ICM45686_HAL_H_ */
