#pragma once
#include <algorithm>

#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/ScenePlayGame.hpp"
#include "../../Controller/States/StateEndGame.hpp"

class StatePlayGame : public StateHandler
{
private:
	std::shared_ptr<ScenePlayGame> m_scenePtr;
	///Draw function
	void draw();
	///Update function
	void update();
	///Handleinput function
	void handleInput();
public:
	StatePlayGame(std::shared_ptr<GameController> gameController);
	~StatePlayGame();
};

