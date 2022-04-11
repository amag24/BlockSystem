#include "liftmotor.h"

#include <iostream>
#include <wiringPi.h>
using namespace std;

int liftpin = 7;  //Correspond à la pin 40

int main(void)//(int argc, char **argv)
{
	if(wiringPiSetup()<0){
		cout<<"setup wiring pi failed"<<endl;
		return 1;
	}
	LiftMotor motor(liftpin);
	while(1){
		motor.advance();
		delay(500);
		motor.stop();
		delay(500);

	cout<<"Blink the LED" << endl;
	}
	
	return 0;
}
