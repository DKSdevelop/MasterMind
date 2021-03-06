// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Controller\GameController.hpp"

#include "Controller\States\StateMainManu.hpp"

int main()
{
	// Create Game Controller
	std::shared_ptr<GameController> gameControllerPtr = std::make_shared<GameController>();

	std::shared_ptr<StateHandler> startMenu = std::make_shared<StateMainManu>(gameControllerPtr);

	gameControllerPtr->pushState(startMenu);

	gameControllerPtr->gameLoop();

	return 0;
}