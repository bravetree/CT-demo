#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include "bcm2835/bcm2835.h"

// LED Pin - wiringPi pin 0 是 BCM_GPIO 17。
//利用 wiringPiSetupSys 进行初始化时必须使用 BCM 编号
//选择其他 pin 编号时，请同时使用 BCM 编号
//更新 Property Pages - Build Events - Remote Post-Build Event 命令
//它使用 gpio 导出进行 wiringPiSetupSys 的设置
#define	LED	17

int main(void)
{
	wiringPiSetupSys();
	//wiringPiI2CSetup(0x10);
	
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(0x10);
	bcm2835_i2c_set_baudrate(400);

	int reg_r_H = 0x01;
	int reg_r_L = 0x02;
	int date_lenth = 0x07;
	//int temp = (reg_r_H << 8) || reg_r_L;
	char buf[8];
	
	while (true)
	{
		bcm2835_i2c_read_register_rs("0x21",&buf[0], 0x07);
		buf[7] = '\0';
		printf("%s", buf);
		//int data = atoi(&buf[0]);

	}
	return 0;
}