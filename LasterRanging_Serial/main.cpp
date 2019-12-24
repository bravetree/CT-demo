#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>

void getTFminiData(int fd, int* distance, int* strength) {
    static char i = 0;
    char j = 0;
    int checksum = 0;
    static int rx[9];
    if (serialDataAvail(fd)) {
        rx[i] = serialGetchar(fd);
        if (rx[0] != 0x59) {
            i = 0;
        }
        else if (i == 1 && rx[1] != 0x59) {
            i = 0;
        }
        else if (i == 8) {
            for (j = 0; j < 8; j++) {
                checksum += rx[j];
            }
            if (rx[8] == (checksum % 256)) {
                *distance = rx[2] + rx[3] * 256;
                *strength = rx[4] + rx[5] * 256;
            }
            i = 0;
        }
        else {
            i++;
        }
    }
}

int main(void)
{
	wiringPiSetupSys();

    int fd = serialOpen("/dev/ttyAMA0", 115200);

	while (true)
	{
        int distance = 0;
        int strength = 0;

        getTFminiData(fd, &distance, &strength);
        while (!distance) {
            getTFminiData(fd, &distance, &strength);
            if (distance) {
                printf("%d", distance);
                printf("cm\t");
                printf("strength: ");
                printf("%d", strength);
            }
        }
	}
	return 0;
}