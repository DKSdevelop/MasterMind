#pragma once
#include <memory>
#include <map>
#include <stack>

#include <SFML/Graphics.hpp>

#include "../Model/GameModel.hpp"
#include "../Model/GameElements/Peg.h"

#include "../View/DrawableGroup.hpp"

class StateHandler;

class GameController
{
private:
//-----------------------------------------------------------------------------
	std::stack<std::shared_ptr<StateHandler>> states_;
	///Is user win game or not
	bool m_gameWon;
//-----------------------------------------------------------------------------
	///used to initialize game parameters start new game/play again
	void initialize();
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
public:
//-----------------------------------------------------------------------------
	std::shared_ptr<GameModel> m_gameModelPtr;
	///Main window
	sf::RenderWindow m_window;
//-----------------------------------------------------------------------------
	GameController();
	~GameController();

	///Push another State to Stack
	void pushState(std::shared_ptr<StateHandler> state);
	///Pop up State from Stack
	void popState();
	///Replace one State to another in Stack
	void changeState(std::shared_ptr<StateHandler> state);
	///Get first State from Stack
	std::shared_ptr<StateHandler> peekState();

	void playAgain(std::shared_ptr<StateHandler> state);

	///Main Game loop
	void gameLoop();
	///Push selected by user balls to PegsRow
	bool pushSelectedColours(std::vector<int>& rowOfColours);
	///Check if selected by user balls are equal to keys
	bool checkResults();
	///Return if game won or not
	bool isGameWon();
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};