#pragma once
#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/SceneEndGame.hpp"

class StateEndGame : public StateHandler
{
private:
	std::shared_ptr<SceneEndGame> m_scenePtr;
	///Draw function
	void draw();
	///Update function
	void update();
	///Handleinput function
	void handleInput();
public:
	StateEndGame(std::shared_ptr<GameController> gameController);
	~StateEndGame();
};

