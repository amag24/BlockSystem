#include "manager.h"

Manager::Manager(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, const std::vector<std::shared_ptr<BlockSection>> &blocks) : _sensors(sensors), _blocks(blocks)
{
	for (auto sensor_it = _sensors.begin(); sensor_it != _sensors.end(); sensor_it++)
	{
		_sensorThreads.push_back(
			std::thread(
				[&]{ this->sense(sensor_it->second); }
			)
		);
	}
	// setup listener and sender threads
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
		} // conditions for other modes
	}

	for (auto sensor = _sensorThreads.begin(); sensor != _sensorThreads.end(); sensor++)
	{
		sensor->join();
	}
}

void Manager::auto_block()
{
	// Automatically update block states according to sensor readings.
	// A request to change mode will propagate states until all blocks are stationary.
	// A request to abort will force all blocks to become stationary without advancing
	// to holding points and then shut down the program.

	bool motion = false;
	while ((!changeMode && !abortRequest) || motion)
	{
		motion = false;
		for (auto block : _blocks)
		{
			// Give the block our current state. Block will set state accordingly and then act
			// When it is finished updating, it will report back if it has seen anything worthy of an abort.
			if (block->update(_sensors, abortRequest, changeMode))
				abortRequest = true;
			// Check if this block is stationary
			if (block->isMoving())
				motion = true;
		}
	}
	if (abortRequest)
		shutdown = true;
}

void Manager::manual_block()
{

}

void Manager::full_manual()
{

}

void Manager::sense(const std::shared_ptr<Sensor> &sensor)
{
	while (!shutdown){
		sensor->sense();
	}
}