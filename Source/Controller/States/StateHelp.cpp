#include "StateHelp.hpp"

#include "StateMainManu.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
StateHelp::StateHelp(std::shared_ptr<GameController> gameController)
{
	m_gameControllerPtr = gameController;
	m_gameModelPtr = m_gameControllerPtr->m_gameModelPtr;
	m_scenePtr = std::shared_ptr<SceneHelp>(new SceneHelp(m_gameModelPtr));
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
StateHelp::~StateHelp()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void StateHelp::draw()
{
	this->m_gameControllerPtr->m_window.clear(sf::Color::Black);

	this->m_gameControllerPtr->m_window.draw(*m_scenePtr);

	return;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void StateHelp::update()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void StateHelp::handleInput()
{
	sf::Event event;
	sf::Vector2i cursorPosition = sf::Mouse::getPosition(this->m_gameControllerPtr->m_window);

	while (this->m_gameControllerPtr->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (this->m_scenePtr->isButtonClicked(cursorPosition.x, cursorPosition.y))
			{
				this->m_gameControllerPtr->popState();
				break;
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