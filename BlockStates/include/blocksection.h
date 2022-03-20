#ifndef BLOCKSECTION_H
#define BLOCKSECTION_H

#include <vector>

#include "statemachine/abstract_state.h"

/////////////////////////Primary block section class, owns a state machine//////////////////////////
class BlockSection
{

public:
    BlockSection(const std::vector<std::string> &watchedSensors);

    friend void connectBlocks(std::shared_ptr<BlockSection> &origin, std::shared_ptr<BlockSection> &destination);

public:
    bool update(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, bool abortRequest, bool stopRequest);


    bool isMoving();

public:
    const State* getState() const;
    

    const std::vector<std::string>& getWatchedSensors();
    

private:
    void transitionStates(const Transition &desiredTransition);

private:
    State* _state = nullptr;
    const std::vector<std::string> _watchedSensors;
    std::shared_ptr<const BlockSection> _nextBlock;
    std::shared_ptr<const BlockSection> _previousBlock;

};

/////////////////////////Helper function to connect two adjacent blocks//////////////////////////
inline void connectBlocks(std::shared_ptr<BlockSection> &origin, std::shared_ptr<BlockSection> &destination)
{
    origin->_nextBlock = std::const_pointer_cast<const BlockSection>(destination);
    destination->_previousBlock = std::const_pointer_cast<const BlockSection>(origin);
}

//////////////Wrapper class to initialize a block into a particular state machine loop///////////////////
template <class initialState>
class Block : public BlockSection
{
public:
    Block(const std::vector<std::string> &watchedSensors) : 
        BlockSection(watchedSensors)
    {
        _state = new initialState();
        _state->onEnter();
    }
};

#endif // BLOCKSECTION_H