#pragma once
#include "GameController.hpp"

#include <memory>

class StateHandler {
protected:
	std::shared_ptr<GameController> m_gameControllerPtr;
	std::shared_ptr<GameModel> m_gameModelPtr;
	//std::shared_ptr<DrawableGroup> m_scenePtr;
public:
	StateHandler();
	virtual ~StateHandler() {}

	///Virtual draw function
	virtual void draw(const float dt) = 0;
	///Virtual update function
	virtual void update(const float dt) = 0;
	///Virtual handleinput function
	virtual void handleInput() = 0;
};