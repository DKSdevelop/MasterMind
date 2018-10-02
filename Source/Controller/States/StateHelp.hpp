#pragma once

#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/SceneHelp.hpp"

class StateHelp: public StateHandler
{
private:
	std::shared_ptr<SceneHelp> m_scenePtr;
	///Draw function
	void draw();
	///Update function
	void update();
	///Handleinput function
	void handleInput();
public:
	StateHelp(std::shared_ptr<GameController> gameController);
	~StateHelp();
};

