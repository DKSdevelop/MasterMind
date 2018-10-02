#include "GameController.hpp"

#include "../Controller/States/StateHandler.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
GameController::GameController()
{
	initialize();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
GameController::~GameController()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void GameController::pushState(std::shared_ptr<StateHandler> state)
{
	this->states_.push(state);

	return;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void GameController::popState()
{
	this->states_.pop();

	return;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void GameController::changeState(std::shared_ptr<StateHandler> state)
{
	if (!this->states_.empty())
	{
		popState();
	}
	pushState(state);

	return;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
std::shared_ptr<StateHandler> GameController::peekState()
{
	if (this->states_.empty())
	{
		return nullptr;
	}
	return this->states_.top();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void GameController::playAgain(std::shared_ptr<StateHandler> state)
{
	while(!this->states_.empty())
	{
		popState();
	}
	initialize();
	pushState(state);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void GameController::gameLoop()
{
	while (this->m_window.isOpen())
	{
		if (peekState() == nullptr)
		{
			continue;
		}

		peekState()->handleInput();

		this->m_window.clear(sf::Color::Black);

		peekState()->draw();
		 
		this->m_window.display();
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool GameController::pushSelectedColours(std::vector<int>& rowOfColours)
{
	int rowIndex = m_gameModelPtr->getGameBoard().getCurrentRow();

	for (int k = 0; k < m_gameModelPtr->getPegsInRow(); ++k)
	{
		PegColor p_color = static_cast<PegColor>(rowOfColours.at(k));
		Peg peg = Peg(p_color, CODE);

		m_gameModelPtr->getGameBoard().addCodePegInRow(rowIndex, peg, k);
	}

	return checkResults();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool GameController::isGameWon()
{
	return m_gameWon;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------