# STM32_ICM45686_I2C

ICM45686の6軸のデータが取れるコードです

SPI通信で実装したい方はこちら（リンク先作成中）

## 使い方

I2CのStandard・Fast Modeに対応しています

(FastPlusは不安定なので非推奨です）

### 設定変更について

Config関数の引数は、Enumで定義してあるので、```icm.Mode::```まで入力すると候補が出てきます

センサーの設定で選べるものはすべて定義したので、選んで使ってください

![スクリーンショット (493)](https://github.com/user-attachments/assets/1dff5040-14f2-4d4b-9303-17537af35aec)


### エラー処理について

**Connection**・**Config**関数は、エラー時の戻り値が違います

(Get_Data関数はエラー時に1つ前の値を返すようにしています）

実際にシステムに組み込む際には、戻り値が0であることを確認することをおすすめします

```cpp
if( icm.Connection() != 0){

	//通信エラーが発生したときの処理
}
```

## Sample Code

UART2を使って、取得したデータを一定間隔ごとに送信しています

TeraTermなどを使ってデータを確認することができます

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
