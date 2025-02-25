# STM32 ICM45686 I2C

STM32でI2C通信でセンサーデータが取れるコードです

** Sample Code**
```cpp

#include "ICM45686.h"
#include "wrapper.hpp"
#include "usart.h"
#include <string>

ICM45686 icm(&hi2c3);

//Buffer
int16_t Gyro_Data[3] = {};
int16_t Accel_Data[3] = {};

//Message
std::string str;

void Send_Data(int16_t data[3]);

void init(){

	icm.Connection();
	icm.Accel_Config(icm.Mode::low_noize, icm.Accel_Scale::scale_02g, icm.ODR::rate_6400hz);
	icm.Gyro_Config(icm.Mode::low_noize, icm.Gyro_Scale::scale_0250dps, icm.ODR::rate_6400hz);
}

void loop(){

	icm.Get_Data(Accel_Data, Gyro_Data);

	Send_Data(Accel_Data);
	Send_Data(Gyro_Data);

	HAL_Delay(10);
}

void Send_Data(int16_t Data[3]){

	str = std::to_string(Data[0]) + " " + std::to_string(Data[1]) + " " + std::to_string(Data[2]) + "\n";

	HAL_UART_Transmit(&huart2, (uint8_t *)str.c_str(),str.length(),100);
}
```
