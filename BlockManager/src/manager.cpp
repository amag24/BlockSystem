#include "manager.h"

Manager::Manager(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, const std::unordered_map<std::string, std::shared_ptr<BlockSection>> &blocks) :
 _sensors(sensors), _blocks(blocks), shutdown(false), changeMode(false), abortRequest(false), lastcommand("")
{
	for (auto sensor_it = _sensors.begin(); sensor_it != _sensors.end(); sensor_it++)
	{
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
	for (auto count : counts){
		std::cout << *count<<std::endl;
	}
	for (auto sensor = _sensorThreads.begin(); sensor != _sensorThreads.end(); sensor++)
	{
		sensor->join();
		std::cout << "Killed sensor thread" << std::endl;
	}
}

void Manager::run()
{
	std::thread operation_thread(&Manager::operate(), this);

	while (!shutdown)
	{
		std::string command;
		std::cin >> command;
		lastcommand = command;
		if (command == "auto")
		{
			changeMode = true;
		} else if(command == "shutdown"){
			std::cout << "Got shutdown request" << std::endl;
			abortRequest = true;
		}
	}

	std::cout << "Leaving Run" << std::endl;
	operation_thread->join();
	std::cout << "Operation thread closed" << std::endl;
}

void Manager::operate(){
	while (!shutdown)
	{
		changeMode = false;
		if (lastcommand == "auto")
		{
			auto_block();
		}
	}
}

void Manager::auto_block()
{
	// Automatically update block states according to sensor readings.
	// A request to change mode will propagate states until all blocks are stationary.
	// A request to abort will force all blocks to become stationary without advancing
	// to holding points and then shut down the program.
	bool motion = false;
	std::cout << "Starting automatic operation" << std::endl;
	while ((!this->changeMode && !this->abortRequest) || motion)
	{
		motion = false;
		for (auto block : this->_blocks)
		{
			// Give the block our current state. Block will set state accordingly and then act
			// When it is finished updating, it will report back if it has seen anything worthy of an abort.
			if (block.second->update(this->_sensors, this->abortRequest, this->changeMode))
				this->abortRequest = true;
			// Check if this block is stationary
			if (block.second->isMoving())
				motion = true;
		}
		delay(10);
	}
	if (this->abortRequest)
		std::cout << "!!!!!!!!!!!!!!ABORT!!!!!!!!!!!!!!"<<std::endl;
		this->shutdown = true;
	
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
		sensor->sense();
		delay(20);
	}
	std::cout << "End of "<<name<<" thread" << std::endl;
}
