#ifndef BLOCKSECTION_H
#define BLOCKSECTION_H

#include <vector>

#include "abstract_state.h"

/////////////////////////Primary block section class, owns a state machine//////////////////////////
class BlockSection
{

public:
    BlockSection(const std::shared_ptr<Actuator> &actuator);
    
    virtual ~BlockSection();

    friend void connectBlocks(std::shared_ptr<BlockSection> &origin, std::shared_ptr<BlockSection> &destination);

public:
    bool update(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, bool abortRequest, bool stopRequest);


    bool isMoving();

    const std::shared_ptr<const State> getState() const;
    
private:
    void transitionStates(const Transition &desiredTransition);

private:
    std::shared_ptr<State> _state;
    std::shared_ptr<Actuator> _actuator;
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
template <class InitialState>
class Block : public BlockSection
{
public:
    Block(const std::shared_ptr<Actuator> &actuator): BlockSection(actuator), _state(new InitialState())
    {
        _state->onEnter();
    }
};

#endif // BLOCKSECTION_H