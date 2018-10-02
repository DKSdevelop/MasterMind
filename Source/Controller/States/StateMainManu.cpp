#include "StateMainManu.hpp"

#include "StatePlayGame.hpp"
#include "StateHelp.hpp"

StateMainManu::StateMainManu(std::shared_ptr<GameController> gameController)
{
	m_gameControllerPtr = gameController;
	m_gameModelPtr = m_gameControllerPtr->m_gameModelPtr;
	m_scenePtr = std::shared_ptr<SceneMainMenu>(new SceneMainMenu(m_gameModelPtr));
}

StateMainManu::~StateMainManu()
{

}

void StateMainManu::draw(const float dt)
{
	this->m_gameControllerPtr->m_window.clear(sf::Color::Black);

	this->m_gameControllerPtr->m_window.draw(*m_scenePtr);

	return;
}

void StateMainManu::update(const float dt)
{
}

void StateMainManu::handleInput()
{
	sf::Event event;
	sf::Vector2i cursorPosition = sf::Mouse::getPosition(this->m_gameControllerPtr->m_window);

	while (this->m_gameControllerPtr->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			switch (this->m_scenePtr->checkWhichButton(cursorPosition.x, cursorPosition.y))
			{
			case 1:
			{
				this->m_gameControllerPtr->pushState(std::make_shared<StatePlayGame>(this->m_gameControllerPtr));
				break;
			}
			case 2:
			{
				this->m_gameControllerPtr->pushState(std::make_shared<StateHelp>(this->m_gameControllerPtr));
				break;
			}
			case 3:
			{
				this->m_gameControllerPtr->m_window.close();
			}
			default: break;
			}
			break;
		}
		if (event.type == sf::Event::Closed)
		{
			this->m_gameControllerPtr->m_window.close();
		}
	}

	return;
}
