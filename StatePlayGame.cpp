#include "StatePlayGame.hpp"

#include <iostream>

StatePlayGame::StatePlayGame(std::shared_ptr<GameController> gameController)
{
	m_gameControllerPtr = gameController;
	m_gameModelPtr = m_gameControllerPtr->m_gameModelPtr;
	m_scenePtr = std::shared_ptr<ScenePlayGame>(new ScenePlayGame(m_gameModelPtr));

	m_gameModelPtr->startGame();
}

StatePlayGame::~StatePlayGame()
{
}

void StatePlayGame::draw(const float dt)
{
	this->m_gameControllerPtr->m_window.clear(sf::Color::Black);

	this->m_gameControllerPtr->m_window.draw(*m_scenePtr);

	return;
}

void StatePlayGame::update(const float dt)
{
}

void StatePlayGame::handleInput()
{
	sf::Event event;
	sf::Vector2i cursorPosition = sf::Mouse::getPosition(this->m_gameControllerPtr->m_window);

	while (this->m_gameControllerPtr->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (this->m_scenePtr->isButtonClicked(cursorPosition.x, cursorPosition.y))
			{
				if (this->m_scenePtr->isRowOfColoursFilled())
				{
					auto rowOfColours = m_scenePtr->getRowOfColour();
					if (this->m_gameControllerPtr->checkSelectedColours(rowOfColours))
					{
						//set END_GAME state
						this->m_gameControllerPtr->pushState(std::make_shared<StateEndGame>(this->m_gameControllerPtr));
						break;
					}
					this->m_scenePtr->clearRowOfColours();
				}
				this->m_scenePtr->clearPlaceAndColours();
			}
			else if (this->m_scenePtr->isColourGrill(cursorPosition.x, cursorPosition.y))
			{
				this->m_scenePtr->chnageSelectedColour(cursorPosition.x);
				/*if (this->m_scenePtr->isPlaceSelected() && this->m_scenePtr->isColourSelected())
				{
					this->m_scenePtr->pushColourToRow();
					this->m_scenePtr->clearPlaceAndColours();
				}*/
			}
			else if (this->m_scenePtr->isMainGrill(cursorPosition.x, cursorPosition.y))
			{
				if (/*this->m_scenePtr->isColourSelected() && */this->m_scenePtr->isPlaceSelected())
				{
					this->m_scenePtr->pushColourToRow();
					this->m_scenePtr->clearPlaceAndColours();
				}
			}
		}
		if (event.type == sf::Event::Closed)
		{
			this->m_gameControllerPtr->m_window.close();
		}
	}

	return;
}