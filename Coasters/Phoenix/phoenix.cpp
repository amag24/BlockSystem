#include "phoenix_states.h"
#include "actuator_includes.h"
#include "manager.h"

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

int main(void)
{
    //SETUP GPIO
    if(wiringPiSetup()<0){
		std::cout<<"setup wiring pi failed"<< std::endl;
		return 1;
	}

    //SETUP SERVO SHIELD
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		std::cout <<"Error in servo shield setup\n" << std::endl;
		return fd;
	}
	pca9685PWMReset(fd);

    //INITIALIZE SENSORS
    std::unordered_map<std::string, std::shared_ptr<Sensor>> sensors;
    sensors["brake"] = std::make_shared<Sensor>(28,5, 18);
    sensors["unload"] = std::make_shared<Sensor>(27,2,14.0);
    sensors["station"] = std::make_shared<Sensor>(22,1,16.0);
    sensors["lift"] = std::make_shared<Sensor>(29,6,15.0);

    //INITIALIZE ACTUATORS
    std::shared_ptr<Actuator> final_brake(new BrakeServo(0, HERTZ, PIN_BASE, MAX_PWM));
    std::shared_ptr<Actuator> unload_wheel(new DriveWheel(1, HERTZ, PIN_BASE, MAX_PWM));
    std::shared_ptr<Actuator> station_wheel(new DriveWheel(2, HERTZ, PIN_BASE, MAX_PWM));
    std::shared_ptr<Actuator> lift_transmitter(new LiftTransmitter(7));

    //INITIALIZE BLOCKS
    std::unordered_map<std::string, std::shared_ptr<BlockSection>> blocks;
    blocks["Gravity"] = std::shared_ptr<BlockSection>(new Block<Phoenix::Brake::Initialize>(final_brake));
    blocks["Unload"] = std::shared_ptr<BlockSection>(new Block<Phoenix::Unload::Initialize>(unload_wheel));
    blocks["Station"] = std::shared_ptr<BlockSection>(new Block<Phoenix::Station::Initialize>(station_wheel));
    blocks["Lift"] = std::shared_ptr<BlockSection>(new Block<Phoenix::Lift::Initialize>(lift_transmitter));

    //CONNECT BLOCKS
    connectBlocks(blocks.at("Gravity"), blocks.at("Unload"));
    connectBlocks(blocks.at("Unload"), blocks.at("Station"));
    connectBlocks(blocks.at("Station"), blocks.at("Lift"));
    connectBlocks(blocks.at("Lift"), blocks.at("Gravity"));

    Manager phoenix(sensors, blocks);
    phoenix.run();
    
    return 0;
}
