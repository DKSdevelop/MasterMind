#pragma once
#include "StateHandler.hpp"
#include "../../Model/GameModel.hpp"

#include "../../View/Scenes/SceneMainMenu.hpp"

class StateMainManu: public StateHandler
{
private:
//-----------------------------------------------------------------------------
	std::shared_ptr<SceneMainMenu> m_scenePtr;
//-----------------------------------------------------------------------------
	///Draw function
	void draw();
	///Update function
	void update();
	///Handleinput function
	void handleInput();
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
public:
//-----------------------------------------------------------------------------
	StateMainManu(std::shared_ptr<GameController> gameController);
	~StateMainManu();
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};

