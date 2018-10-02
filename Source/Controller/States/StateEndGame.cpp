#include "StateEndGame.hpp"
#include "StateMainManu.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
StateEndGame::StateEndGame(std::shared_ptr<GameController> gameController)
{
	m_gameControllerPtr = gameController;
	m_gameModelPtr = m_gameControllerPtr->m_gameModelPtr;
	m_scenePtr = std::shared_ptr<SceneEndGame>(new SceneEndGame(m_gameModelPtr));

	m_scenePtr->setGameScore(m_gameControllerPtr->isGameWon());
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
StateEndGame::~StateEndGame()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void StateEndGame::draw()
{
	this->m_gameControllerPtr->m_window.clear(sf::Color::Black);

	this->m_gameControllerPtr->m_window.draw(*m_scenePtr);

	return;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void StateEndGame::update()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void StateEndGame::handleInput()
{
	sf::Event event;
	sf::Vector2i cursorPosition = sf::Mouse::getPosition(this->m_gameControllerPtr->m_window);

	while (this->m_gameControllerPtr->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (this->m_scenePtr->isButtonClicked(cursorPosition.x, cursorPosition.y))
			{
				if (this->m_scenePtr->wantPlayAgain())
				{
					this->m_gameControllerPtr->playAgain(std::make_shared<StateMainManu>(this->m_gameControllerPtr));
					break;
				}
				else
				{
					this->m_gameControllerPtr->m_window.close();
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------