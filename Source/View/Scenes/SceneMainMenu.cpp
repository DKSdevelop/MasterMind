#include "SceneMainMenu.hpp"



SceneMainMenu::SceneMainMenu(std::shared_ptr<GameModel> gameModel)
	: m_gameModelPtr(gameModel)
{
	m_width = 1000 / 4;
	m_hight = 900 / 8;
	m_separator = m_hight / 4;
	m_x = 1000 / 2 - m_width / 2;
	m_y = 900 / 2 - m_hight / 2 - m_separator - m_hight;

	for (int i = 0; i < 3; ++i)
	{
		m_coords.push_back(sf::Vector2i(m_x, m_y + i * (m_hight + m_separator)));
	}
}

SceneMainMenu::~SceneMainMenu()
{
}

int SceneMainMenu::checkWhichButton(int x_pos, int y_pos)
{
	for (int i = 0; i < 3; ++i)
	{
		if (x_pos >= m_coords.at(i).x && x_pos <= m_coords.at(i).x + m_width
			&& y_pos >= m_coords.at(i).y && y_pos <= m_coords.at(i).y + m_hight)
		{
			return i + 1;
		}
	}
	return 0;
}

void SceneMainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < 3; ++i)
	{
		float x = (float)(m_coords.at(i).x);
		float y = (float)(m_coords.at(i).y);

		sf::RectangleShape m_button;
		m_button.setSize(sf::Vector2f(m_width, m_hight));
		m_button.setFillColor(sf::Color::Black);
		m_button.setOutlineThickness(2);
		m_button.setOutlineColor(sf::Color::White);
		m_button.setFillColor(sf::Color(89, 89, 89));
		m_button.setPosition(sf::Vector2f(x, y));

		target.draw(m_button, states);

		sf::Text text;
		text.setFont(m_font);
		text.setCharacterSize(60);
		text.setFillColor(sf::Color::White);
		text.setString(m_options.at(i));

		float textBegin_x = x + (m_width - text.getLocalBounds().width) / 2;
		float textBegin_y = y + (m_hight - text.getLocalBounds().height) / 2;

		text.setPosition(textBegin_x, textBegin_y);

		target.draw(text, states);
	}
}
