#include "GameController.hpp"

#include "StateHandler.hpp"

GameController::GameController()
{
	initialize();
}

GameController::~GameController()
{
}

void GameController::initialize()
{
	if (!m_window.isOpen())
	{
		this->m_window.create(sf::VideoMode(1000, 900), "Master Mind");
	}
	m_window.clear();
	// Create Game Model
	if (m_gameModelPtr)
	{
		m_gameModelPtr.reset(new GameModel(12, 4));
	}
	else
	{
		m_gameModelPtr = std::make_shared<GameModel>(12, 4);
	}

	m_gameWon = false;
}

void GameController::pushState(std::shared_ptr<StateHandler> state)
{
	this->states_.push(state);

	return;
}

void GameController::popState()
{
	this->states_.pop();

	return;
}

void GameController::changeState(std::shared_ptr<StateHandler> state)
{
	if (!this->states_.empty())
	{
		popState();
	}
	pushState(state);

	return;
}

std::shared_ptr<StateHandler> GameController::peekState()
{
	if (this->states_.empty())
	{
		return nullptr;
	}
	return this->states_.top();
}

void GameController::playAgain(std::shared_ptr<StateHandler> state)
{
	while(!this->states_.empty())
	{
		popState();
	}
	initialize();
	pushState(state);
}

void GameController::gameLoop()
{
	//sf::Clock clock;

	while (this->m_window.isOpen())
	{
		//sf::Time elapsed = clock.restart();
		//float dt = elapsed.asSeconds();

		if (peekState() == nullptr)
		{
			continue;
		}

		peekState()->handleInput();
		//peekState()->update(dt);

		this->m_window.clear(sf::Color::Black);
		float dt = 0;
		peekState()->draw(dt);
		//this->m_window.draw(*peekState()->getDrawableObject());
		 
		this->m_window.display();
	}
}
bool GameController::checkSelectedColours(std::vector<int>& rowOfColours)
{
	int rowIndex = m_gameModelPtr->getGameBoard().getCurrentRow();

	for (int k = 0; k < m_gameModelPtr->getPegsInRow(); ++k)
	{
		PegColor p_color = static_cast<PegColor>(rowOfColours.at(k));
		Peg peg = Peg(p_color, CODE);

		if (m_gameModelPtr->getGameBoard().addCodePegInRow(rowIndex, peg, k))
		{
			//return true;
		}
	}

	return checkResults();
}

bool GameController::checkResults()
{
	PegRow row = m_gameModelPtr->getGameBoard().getVecOfPegRows().at(m_gameModelPtr->getGameBoard().getCurrentRow());
	m_gameWon = false;

	if (row.IsCodePegsAndKeyPegsAreEqual())
	{
		m_gameWon = true;
		return true;
	}
	else
	{
		if (m_gameModelPtr->getGameBoard().incraseCurrentRow())
		{
			return true;
		}
	}

	return false;
}

bool GameController::isGameWon()
{
	return m_gameWon;
}
