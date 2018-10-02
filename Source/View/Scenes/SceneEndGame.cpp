#include "SceneEndGame.hpp"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
SceneEndGame::SceneEndGame(std::shared_ptr<GameModel> gameModel)
	: m_gameModelPtr(gameModel)
{
	m_winGame = false;
	m_playAgain = false;

	m_width = 1000 / 4;
	m_hight = 900 / 8;

	m_x = 1000 / 2 - m_width / 2;
	m_y = 900 / 2 - m_hight / 2;

	m_buttonPlayAgain.setSize(sf::Vector2f(m_width, m_hight));
	m_buttonPlayAgain.setFillColor(sf::Color::Black);
	m_buttonPlayAgain.setOutlineThickness(2);
	m_buttonPlayAgain.setOutlineColor(sf::Color::White);
	m_buttonPlayAgain.setFillColor(sf::Color(89, 89, 89));
	m_buttonPlayAgain.setPosition(sf::Vector2f(0, 0));

	textPlayAgain.setFont(m_font);
	textPlayAgain.setCharacterSize(60);
	textPlayAgain.setFillColor(sf::Color::White);
	textPlayAgain.setString("Play Again");

	float textPlayAgainBegin_x = 0 + (m_width - textPlayAgain.getLocalBounds().width) / 2;
	float textPlayAgainBegin_y = 0 + (m_hight - textPlayAgain.getLocalBounds().height) / 2;

	textPlayAgain.setPosition(textPlayAgainBegin_x, textPlayAgainBegin_y);

	m_buttonExit.setSize(sf::Vector2f(m_width, m_hight));
	m_buttonExit.setFillColor(sf::Color::Black);
	m_buttonExit.setOutlineThickness(2);
	m_buttonExit.setOutlineColor(sf::Color::White);
	m_buttonExit.setFillColor(sf::Color(89, 89, 89));
	m_buttonExit.setPosition(sf::Vector2f(1000 - m_width, 0));

	textExit.setFont(m_font);
	textExit.setCharacterSize(60);
	textExit.setFillColor(sf::Color::White);
	textExit.setString("Close");

	float textExitBegin_x = (1000 - m_width) + (m_width - textExit.getLocalBounds().width) / 2;
	float textExitBegin_y = 0 + (m_hight - textExit.getLocalBounds().height) / 2;

	textExit.setPosition(textExitBegin_x, textExitBegin_y);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
SceneEndGame::~SceneEndGame()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SceneEndGame::isButtonClicked(int x_pos, int y_pos)
{
	if (x_pos >= m_buttonPlayAgain.getGlobalBounds().left && x_pos <= m_buttonPlayAgain.getGlobalBounds().left + m_buttonPlayAgain.getGlobalBounds().width
		&& y_pos >= m_buttonPlayAgain.getGlobalBounds().top && y_pos <= m_buttonPlayAgain.getGlobalBounds().top + m_buttonPlayAgain.getGlobalBounds().height)
	{
		m_playAgain = true;
		return true;
	}
	else if (x_pos >= m_buttonExit.getGlobalBounds().left && x_pos <= m_buttonExit.getGlobalBounds().left + m_buttonExit.getGlobalBounds().width
		&& y_pos >= m_buttonExit.getGlobalBounds().top && y_pos <= m_buttonExit.getGlobalBounds().top + m_buttonExit.getGlobalBounds().height)
	{
		m_playAgain = false;
		return true;
	}

	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void SceneEndGame::setGameScore(bool score)
{
	m_winGame = score;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SceneEndGame::wantPlayAgain()
{
	return m_playAgain;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void SceneEndGame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_buttonPlayAgain, states);
	target.draw(textPlayAgain, states);

	target.draw(m_buttonExit, states);
	target.draw(textExit, states);

	sf::Text scoreText;
	scoreText.setFont(m_font);
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(sf::Color::White);
	std::string endmessage = m_winGame ? "You Win !!!" : "You Loose";
	scoreText.setString(endmessage);

	float scoreTextTextBegin_x = m_x + (m_width - scoreText.getLocalBounds().width) / 2;
	float scoreTextTextBegin_y = m_y + (m_hight - scoreText.getLocalBounds().height) / 2;

	scoreText.setPosition(scoreTextTextBegin_x, scoreTextTextBegin_y);

	target.draw(scoreText, states);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------