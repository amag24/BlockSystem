#include "manager.h"

Manager::Manager(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, const std::vector<std::shared_ptr<BlockSection>> &blocks) : _sensors(sensors), _blocks(blocks)
{
	for (auto sensor_it = _sensors.begin(); sensor_it != _sensors.end(); sensor_it++)
	{
		_sensorThreads.push_back(
			std::thread(
				[&]{ this->sense(sensor_it->first); }
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
			// Fetch the sensors and mutexes relevant to this block only.
			std::unordered_map<std::string, std::shared_ptr<Sensor>> sensors;
			for (auto sensorname : block->getWatchedSensors())
			{
				getMutex(sensorname).lock();
				sensors[sensorname] = _sensors[sensorname];
			}
			// Give the block our current state. Block will set state accordingly and then act
			// When it is finished updating, it will report back if it has seen anything worthy of an abort.
			if (block->update(sensors, abortRequest, changeMode))
				abortRequest = true;
			// Check if this block is stationary
			if (block->isMoving())
				motion = true;
			// Release the sensor mutexes for this block
			for (auto sensorname : block->getWatchedSensors())
			{
				getMutex(sensorname).unlock();
			}
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

std::mutex& Manager::getMutex(const std::string& name)
{
	std::lock_guard<std::mutex> m_lock(mapMutex);
	return _sensorMutexes[name];
}

void Manager::sense(const std::string &sensor_name)
{
	while (!shutdown){
		std::lock_guard<std::mutex> s_lock(getMutex(sensor_name));
		_sensors[sensor_name]->sense();
	}
}