/*
 * ICM45686.h
 *
 *  Created on: Dec 17, 2024
 *      Author: aoi25
 */

#ifndef INC_ICM45686_H_
#define INC_ICM45686_H_

#include "ICM45686_HAL.h"

class ICM45686: private ICM45686_HAL {

	public:

		enum class mode: uint8_t{

			off = 0x00,
			standby,
			low_power,
			low_noize
		};

		enum class accel_scale: uint8_t{

			scale_32g = 0x00,
			scale_16g,
			scale_08g,
			scale_04g,
			scale_02g
		};

		enum class gyro_scale: uint8_t{

			scale_4000dps = 0x00,
			scale_2000dps,
			scale_1000dps,
			scale_0500dps,
			scale_0250dps,
			scale_0125dps,
			scale_0062dps,
			scale_0031dps,
			scale_0015dps,
			scale_0006dps

		};

		enum class odr: uint8_t{

			rate_6400hz = 3,
			rate_3200hz,
			rate_1600hz,
			rate_0800hz,
			rate_0400hz,
			rate_0200hz,
			rate_0100hz,
			rate_0050hz,
			rate_0025hz,
			rate_0012hz,
			rate_0006hz,
			rate_0003hz,
			rate_0001hz
		};

		ICM45686(I2C_HandleTypeDef* i2c_pin);

		uint8_t verify_connection();
		uint8_t accel_mode(ICM45686::mode, ICM45686::accel_scale, ICM45686::odr);
		uint8_t gyro_mode(ICM45686::mode, ICM45686::gyro_scale, ICM45686::odr);
		uint8_t get_data(int16_t accel_buffer[3], int16_t gyro_buffer[3]);

	private:

		I2C_HandleTypeDef* i2c_pin;
		uint8_t raw_data[12];

};

#endif /* INC_ICM45686_H_ */
