#pragma once
#include <algorithm>

#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/ScenePlayGame.hpp"
#include "../../Controller/States/StateEndGame.hpp"

class StatePlayGame : public StateHandler
{
public:
	StatePlayGame(std::shared_ptr<GameController> gameController);
	~StatePlayGame();
private:
	std::shared_ptr<ScenePlayGame> m_scenePtr;
	///Draw function
	void draw(const float dt);
	///Update function
	void update(const float dt);
	///Handleinput function
	void handleInput();
};

