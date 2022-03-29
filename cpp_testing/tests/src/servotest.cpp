#include "pca9685.h"

#include <wiringPi.h>

#include <iostream>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

int brakerun = PIN_BASE + 0; 
int transfer = PIN_BASE + 1;
int station = PIN_BASE + 2;

/**
 * Calculate the number of ticks the signal should be high for the required amount of time
 */
int calcTicks(float impulseMs)
{
	return (int)(MAX_PWM * HERTZ *impulseMs/1000 + 0.5f);
}

/**
 * input is [0..1]
 * output is [min..max]
 */
float map(float input, float min, float max)
{
	return (input * max) + (1 - input) * min;
}

int main(void)//(int argc, char **argv)
{
	if(wiringPiSetup()<0){
		std::cout<<"setup wiring pi failed"<<std::endl;
		return 1;
	}
	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		std::cout <<"Error in setup\n" << std::endl;
		return fd;
	}

	// Reset all output
	pca9685PWMReset(fd);
	
	while (1){
			pwmWrite(brakerun, calcTicks(1));
			pwmWrite(transfer, calcTicks(1.5));
			pwmWrite(station, calcTicks(1.5));
			delay(2000);
			pwmWrite(brakerun, calcTicks(2));
			pwmWrite(transfer, calcTicks(1));
			pwmWrite(station, calcTicks(1.1));
			delay(2000);
	}
	return 0;
}
