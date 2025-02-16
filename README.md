# STM32_ICM45686

とりあえず動きました！！！

## サンプルコード

```cpp
#include "wrapper.hpp"
#include "ICM45686.h"
#include "usart.h"
#include <string>

ICM45686 icm(&hi2c3);

int16_t gyro_data[3];
int16_t accel_data[3];

void send_data(int16_t data[3]);

void init(){

	icm.verify_connection();
	icm.accel_mode(icm.mode::low_noize, icm.accel_scale::scale_02g, icm.odr::rate_0800hz);
	icm.gyro_mode(icm.mode::low_noize, icm.gyro_scale::scale_0250dps, icm.odr::rate_0800hz);
}

void loop(){

	uint8_t is_get = icm.get_data(accel_data, gyro_data);
	
	if(is_get == 0){

		send_data(gyro_data);
		send_data(accel_data);

		is_get = 1;
	}
}

void send_data(int16_t data[3]){

	std::string str;
	str = std::to_string(data[0]) + " " + std::to_string(data[1]) + " " + std::to_string(data[2]) + "\n";

	HAL_UART_Transmit(&huart2, (uint8_t *)str.c_str(),str.length(),100);
}
```
