#include <iostream>
#include <wiringPi.h>

#include "sensor.h"
#include <thread>
int mpin = 29;  
int tpin = 6;


int main(void)//(int argc, char **argv)
{
	if(wiringPiSetup()<0){
		std::cout<<"setup wiring pi failed"<< std::endl;
		return 1;
	}
	Sensor sensor(mpin, tpin);
	while(1){
		std::string report = "";
		//~ int value = static_cast<int>(sensor.sense());
		//~ for (int i=0.0; i<(value % 10); i++)
			//~ report += "|";
		std::cout << (sensor.sense()*0.02) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	}
	
	return 0;
}
