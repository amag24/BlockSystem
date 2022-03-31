#ifndef BLOCKSECTION_H
#define BLOCKSECTION_H

#include <vector>

#include "statemachine/abstract_state.h"

/////////////////////////Primary block section class, owns a state machine//////////////////////////
class BlockSection
{

public:
    BlockSection();
    
    ~BlockSection();

    friend void connectBlocks(std::shared_ptr<BlockSection> &origin, std::shared_ptr<BlockSection> &destination);

public:
    bool update(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, bool abortRequest, bool stopRequest);


    bool isMoving();

    const State* getState() const;
    
private:
    void transitionStates(const Transition &desiredTransition);

private:
    State* _state = nullptr;
    std::shared_ptr<const BlockSection> _nextBlock;
    std::shared_ptr<const BlockSection> _previousBlock;

};

/////////////////////////Helper function to connect two adjacent blocks//////////////////////////
inline void connectBlocks(std::shared_ptr<BlockSection> &origin, std::shared_ptr<BlockSection> &destination);

//////////////Wrapper class to initialize a block into a particular state machine loop///////////////////
template <class InitialState>
class Block : public BlockSection
{
public:
    Block() 
    {
        _state = new InitialState();
        _state->onEnter();
    }
};

#endif // BLOCKSECTION_H