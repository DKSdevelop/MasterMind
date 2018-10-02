#pragma once
#include "../GameController.hpp"

#include <memory>

class StateHandler
{
protected:
//-----------------------------------------------------------------------------
	std::shared_ptr<GameController> m_gameControllerPtr;
	std::shared_ptr<GameModel> m_gameModelPtr;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
public:
//-----------------------------------------------------------------------------
	StateHandler();
	virtual ~StateHandler() {}

	///Virtual draw function
	virtual void draw() = 0;
	///Virtual update function
	virtual void update() = 0;
	///Virtual handleinput function
	virtual void handleInput() = 0;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};