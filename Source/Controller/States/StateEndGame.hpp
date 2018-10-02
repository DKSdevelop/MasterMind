#pragma once
#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/SceneEndGame.hpp"

class StateEndGame : public StateHandler
{
public:
	StateEndGame(std::shared_ptr<GameController> gameController);
	~StateEndGame();
private:
	std::shared_ptr<SceneEndGame> m_scenePtr;
	///Draw function
	void draw(const float dt);
	///Update function
	void update(const float dt);
	///Handleinput function
	void handleInput();
};

