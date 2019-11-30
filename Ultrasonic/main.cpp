/*******************************
*    Ultra Sonic Raning module Pin VCC should
*  be connected to 5V power.
******************************/
#include <wiringPi.h>
#include <stdio.h>

#include <time.h>
#define Trig    16
#define Echo    17

void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}

float disMeasure(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long time1, time2;
	float dis;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);      //��������������
	digitalWrite(Trig, LOW);

	while (!(digitalRead(Echo) == 1));
	gettimeofday(&tv1, NULL);           //��ȡ��ǰʱ��

	while (!(digitalRead(Echo) == 0));
	gettimeofday(&tv2, NULL);           //��ȡ��ǰʱ��

	time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;   //΢�뼶��ʱ��
	time2 = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis = (float)(time2 - time1) / 1000000 * 34000 / 2;  //�������

	return dis;
}

int main(void)
{
	float dis;

	if (wiringPiSetup() == -1) { //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1;
	}

	ultraInit();

	while (1) {
		dis = disMeasure();
		printf("%0.2f cm\n\n", dis);
		delay(300);
	}

	return 0;
}
