# STM32_ICM45686
now debug

## サンプルコード

```cpp
#include "ICM45686.h"

ICM45686 icm(&hi2c2);

int16_t gyro_data[3];
int16_t accel_data[3];

void init(){

	icm.verify_connection();
	icm.accel_mode(icm.mode::low_noize, icm.accel_scale::scale_02g, icm.odr::rate_6400hz);
	icm.gyro_mode(icm.mode::low_noize, icm.gyro_scale::scale_0250dps, icm.odr::rate_6400hz);
}

void loop(){

	icm.get_data(accel_data, gyro_data);
}
```
