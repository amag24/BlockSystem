#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <unordered_map>
#include <thread>
#include <iostream>
#include <mutex>

#include "blocksection.h"

class Manager
{

public:
    Manager(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, const std::vector<std::shared_ptr<BlockSection>> &blocks);  
    

public:
    void run();

    void auto_block();

    void manual_block();//run manual block listener and sender threads

    void full_manual();//run full manual listener and sender threads


private:
    std::mutex& getMutex(const std::string& name);

    void sense(const std::string &sensor_name);

private:
    std::unordered_map<std::string, std::shared_ptr<Sensor>> _sensors;
    std::vector<std::thread> _sensorThreads;
    std::unordered_map<std::string, std::mutex> _sensorMutexes;
    std::mutex mapMutex;

    std::vector<std::shared_ptr<BlockSection>> _blocks;

    bool shutdown = false;
    bool abortRequest = false;
    bool changeMode = false;
};

#endif // MANAGER_H