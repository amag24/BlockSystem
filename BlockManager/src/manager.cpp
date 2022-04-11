#include "manager.h"

Manager::Manager(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, const std::unordered_map<std::string, std::shared_ptr<BlockSection>> &blocks) : _sensors(sensors), _blocks(blocks), shutdown(false)
{
	std::cout << "Manager Constructor" << std::endl;
	for (auto sensor_it = _sensors.begin(); sensor_it != _sensors.end(); sensor_it++)
	{
		std::cout << "Starting thread for sensor "<<sensor_it->first << std::endl;
		std::shared_ptr<std::atomic<int>> c = std::make_shared<std::atomic<int>>(0);
		counts.push_back(c);
		_sensorThreads.push_back(
			std::thread(
				[=]{  this->sense(c, sensor_it->first,sensor_it->second); }
			)
		);
	}
	// setup listener and sender threads
}

Manager::~Manager()
{
	std::cout << "Manager Destructor" << std::endl;
	for (auto count : counts){
		std::cout << *count<<std::endl;
	}
	for (auto sensor = _sensorThreads.begin(); sensor != _sensorThreads.end(); sensor++)
	{
		if (sensor->joinable()){
		std::cout << "Trying to kill sensor thread" << std::endl;
		sensor->join();
		std::cout << "Successfully killed sensor thread" << std::endl;
		} else {
			std::cout << "thread already closed" << std::endl;
		}
	}
}

void Manager::run()
{
	while (!shutdown)
	{
		std::string command;
		std::cin >> command;
		if (command == "auto")
		{
			auto_block();
		} else if(command == "shutdown"){
			std::cout << "Got shutdown request" << std::endl;
			shutdown = true;
		}
	}
	std::cout << "Leaving Run" << std::endl;
}

void Manager::auto_block()
{
	// Automatically update block states according to sensor readings.
	// A request to change mode will propagate states until all blocks are stationary.
	// A request to abort will force all blocks to become stationary without advancing
	// to holding points and then shut down the program.

	bool motion = false;
	std::cout << "Starting automatic operation" << std::endl;
	while ((!changeMode && !abortRequest) || motion)
	{
		motion = false;
		for (auto block : _blocks)
		{
			// Give the block our current state. Block will set state accordingly and then act
			// When it is finished updating, it will report back if it has seen anything worthy of an abort.
			if (block.second->update(_sensors, abortRequest, changeMode))
				abortRequest = true;
			// Check if this block is stationary
			if (block.second->isMoving())
				motion = true;
		}
		delay(10);
	}
	if (abortRequest)
		std::cout << "!!!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!"<<std::endl;
		shutdown = true;
}

void Manager::manual_block()
{

}

void Manager::full_manual()
{

}

void Manager::sense(std::shared_ptr<std::atomic<int>> count, std::string name, const std::shared_ptr<Sensor> &sensor)
{
	std::cout << "Start of "<<name<<" thread" << std::endl;
	while (!shutdown){
		*count = *count + 1;
		//~ std::cout << name << " sensing before"<< std::endl;
		sensor->sense();
		//~ std::cout << name << " sensing after" << shutdown << std::endl;
		delay(20);
	}
	delay(3);
	std::cout << "End of "<<name<<" thread" << std::endl;
}
