#pragma once
#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/SceneMainMenu.hpp"

class StateMainManu: public StateHandler
{
public:
	StateMainManu(std::shared_ptr<GameController> gameController);
	~StateMainManu();
private:
	std::shared_ptr<SceneMainMenu> m_scenePtr;
	///Draw function
	void draw(const float dt);
	///Update function
	void update(const float dt);
	///Handleinput function
	void handleInput();
};

