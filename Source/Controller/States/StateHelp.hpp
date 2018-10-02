#pragma once

#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/SceneHelp.hpp"

class StateHelp: public StateHandler
{
public:
	StateHelp(std::shared_ptr<GameController> gameController);
	~StateHelp();

private:
	std::shared_ptr<SceneHelp> m_scenePtr;
	///Draw function
	void draw(const float dt);
	///Update function
	void update(const float dt);
	///Handleinput function
	void handleInput();
};

