#include "SceneHelp.hpp"



SceneHelp::SceneHelp(std::shared_ptr<GameModel> gameModel)
	: m_gameModelPtr(gameModel)
{
	m_font.loadFromFile("Gobold Blocky Regular.otf");

	m_width = 1000 / 4;
	m_hight = 900 / 8;
}

SceneHelp::~SceneHelp()
{
}

bool SceneHelp::isButtonClicked(int x_pos, int y_pos)
{
	if (x_pos >= 0 && x_pos <= m_width
		&& y_pos >= 0 && y_pos <= m_hight)
	{
		return true;
	}
	return false;
}

void SceneHelp::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::RectangleShape m_button;
	m_button.setSize(sf::Vector2f(m_width, m_hight));
	m_button.setFillColor(sf::Color::Black);
	m_button.setOutlineThickness(2);
	m_button.setOutlineColor(sf::Color::White);
	m_button.setFillColor(sf::Color(89, 89, 89));
	m_button.setPosition(sf::Vector2f(0, 0));

	target.draw(m_button, states);

	sf::Text text;
	text.setFont(m_font);
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::White);
	text.setString("Main Menu");

	float textBegin_x = 0 + (m_width - text.getLocalBounds().width) / 2;
	float textBegin_y = 0 + (m_hight - text.getLocalBounds().height) / 2;

	text.setPosition(textBegin_x, textBegin_y);

	target.draw(text, states);
}
