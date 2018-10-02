#pragma once
#include <memory>
#include <map>
#include <stack>

#include <SFML/Graphics.hpp>

#include "../Model/GameModel.hpp"
#include "../Model/GameElements/Peg.h"

#include "../View/DrawableGroup.hpp"

class StateHandler;

enum StateName
{
	MAIN_MENU = 0,
	GAME_IN_PROGRESS,
	GAME_ENDED,
	HELP_MODE,
};

class GameController
{
private:
	std::stack<std::shared_ptr<StateHandler>> states_;
	bool m_gameWon;

	void initialize();
public:
	std::shared_ptr<GameModel> m_gameModelPtr;
	///Main window
	sf::RenderWindow m_window;

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

	bool checkSelectedColours(std::vector<int>& rowOfColours);

	bool checkResults();

	bool isGameWon();

	GameController();
	~GameController();
};