#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <unordered_map>
#include <thread>
#include <atomic>
#include <iostream>

#include "blocksection.h"

class Manager
{

public:
    Manager(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, const std::unordered_map<std::string, std::shared_ptr<BlockSection>> &blocks);  
    
    ~Manager();
    
public:
    void run();

    void auto_block();

    void manual_block();//run manual block listener and sender threads

    void full_manual();//run full manual listener and sender threads


private:
    void sense(std::shared_ptr<std::atomic<int>> count, std::string name, const std::shared_ptr<Sensor> &sensor);

private:
    std::unordered_map<std::string, std::shared_ptr<Sensor>> _sensors;
    std::vector<std::thread> _sensorThreads;
    std::unordered_map<std::string, std::shared_ptr<BlockSection>> _blocks;
    std::vector<std::shared_ptr<std::atomic<int>>> counts;
    std::atomic<bool> shutdown;
    bool abortRequest = false;
    bool changeMode = false;
};

#endif // MANAGER_H
