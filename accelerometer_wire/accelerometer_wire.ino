// ---------------------------------------------------------------
/*
	accelerometer_wire.ino

						Aug/06/2021
*/
// ---------------------------------------------------------------
#include <Wire.h>

#define INTERVAL	(5000)
 
// デバイスアドレス(スレーブ)
uint8_t DEVICE_ADDRESS = 0x53;	
 
// XYZレジスタ用のテーブル(6byte)
uint8_t RegTbl[6];	

// ---------------------------------------------------------------
void setup() {
	// マスタとしてI2Cバスに接続する
	Wire.begin();			 
 
	// DATA_FORMAT(データ形式の制御) 
	Wire.beginTransmission(DEVICE_ADDRESS);	
		// DATA_FORMATのアドレス		
		Wire.write(0x31);
		// 「最大分解能モード」 及び 「±16g」 (0x0B == 1011)
		Wire.write(0x0B);	
		// 「10bit固定分解能モード」 及び　「±16g」にする場合 (0x03 == 0011)
		// Wire.write(0x03);
	Wire.endTransmission();
 
	// POWER_TCL(節電機能の制御) 
	Wire.beginTransmission(DEVICE_ADDRESS);	
		// POWER_CTLのアドレス		
		Wire.write(0x2d);
		// 測定モードにする
		Wire.write(0x08);	
	Wire.endTransmission();
}
 
// ---------------------------------------------------------------
void loop() {
	// XYZの先頭アドレスに移動する
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x32);
	Wire.endTransmission();
	
	// デバイスへ6byteのレジスタデータを要求する
	Wire.requestFrom(DEVICE_ADDRESS, 6);
	 
	// 6byteのデータを取得する
	int i;
	for (i=0; i< 6; i++){
		while (Wire.available() == 0 ){}
		RegTbl[i] = Wire.read();
	}
 
	// データを各XYZの値に変換する(LSB単位)
	int16_t xx = (((int16_t)RegTbl[1]) << 8) | RegTbl[0];
	int16_t yy = (((int16_t)RegTbl[3]) << 8) | RegTbl[2];
	int16_t zz = (((int16_t)RegTbl[5]) << 8) | RegTbl[4];	
 
	SerialUSB.print("WIRE: X: ");
	SerialUSB.print( xx);
	SerialUSB.print(" Y: ");
	SerialUSB.print( yy);
	SerialUSB.print(" Z: ");
	SerialUSB.print( zz);
	SerialUSB.println("");
 
	delay(INTERVAL);
}

// ---------------------------------------------------------------
