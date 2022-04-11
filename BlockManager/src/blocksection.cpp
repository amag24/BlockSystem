#include "blocksection.h"

BlockSection::BlockSection(const std::shared_ptr<State> &initial_state, const std::shared_ptr<Actuator> &actuator) : _state(initial_state), _actuator(actuator)
{
}

BlockSection::~BlockSection(){
	if(_state)
	{
		_state->onExit();
	}
}

bool BlockSection::update(const std::unordered_map<std::string, std::shared_ptr<Sensor>> &sensors, bool abortRequest, bool stopRequest)
{
	if (_state)
	{
		// Ask state if it wants to transition
		std::unique_ptr<Transition> desiredTransition = _state->getTransition(sensors, abortRequest, stopRequest, _previousBlock->getState(), _nextBlock->getState());

		// If there is a transition, execute it
		if (*desiredTransition)
			transitionStates(desiredTransition);
		_state->act(_actuator);
		//~ if (_state->shouldAbort()){
			//~ _state->act(_actuator);
			//~ _state->act(_actuator);
			//~ _state->act(_actuator);
		//~ }
		return _state->shouldAbort();
	} else {
		return true;
	}
}

bool BlockSection::isMoving()
{
	if (_state)
		return _state->is_moving();
	return false;
}
   
const std::shared_ptr<const State> BlockSection::getState() const 
{
	return std::const_pointer_cast<const State>(_state);
}

void BlockSection::transitionStates(const std::unique_ptr<Transition> &desiredTransition)
{
	if (_state)
	{
		_state->onExit();
		_state = std::shared_ptr<State>(desiredTransition->newState());
		_state->onEnter();
	} else {
		throw std::runtime_error("State did not exist... something is very weird");
	}
}



