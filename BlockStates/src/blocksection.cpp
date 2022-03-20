#include "blocksection.h"

BlockSection::BlockSection(const std::vector<std::string> &watchedSensors) : 
    _watchedSensors(watchedSensors)
{
}

bool BlockSection::update(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, bool abortRequest, bool stopRequest)
{
	if (_state)
	{
		// Check state of previous and/or next block
		const State *previousState = _previousBlock ? _previousBlock->getState() : nullptr;
		const State *nextState = _nextBlock ? _nextBlock->getState() : nullptr;

		// Ask state if it wants to transition
		Transition desiredTransition = _state->getTransition(sensors, abortRequest, stopRequest, previousState, nextState);

		// If there is a transition, execute it
		if (desiredTransition)
			transitionStates(desiredTransition);
		_state->act();
		return _state->shouldAbort();
	}
}

bool BlockSection::isMoving()
{
	if (_state)
		return _state->is_moving();
	return false;
}
   
const State* BlockSection::getState() const 
{
	return _state;
}

const std::vector<std::string>& BlockSection::getWatchedSensors()
{
	return _watchedSensors;
} 

void BlockSection::transitionStates(const Transition &desiredTransition)
{
	_state->onExit();
	delete _state;
	_state = desiredTransition.newState();
	_state->onEnter();
}