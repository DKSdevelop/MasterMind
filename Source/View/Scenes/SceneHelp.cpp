#include "SceneHelp.hpp"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
SceneHelp::SceneHelp(std::shared_ptr<GameModel> gameModel)
	: m_gameModelPtr(gameModel)
{
	m_width = 1000 / 4;
	m_hight = 900 / 8;

	std::shared_ptr<sf::Text> m_descriptionText = std::make_shared<sf::Text>(sf::Text());
	m_descriptionText->setFont(m_font);
	m_descriptionText->setCharacterSize(30);
	m_descriptionText->setFillColor(sf::Color::White);

	m_file.open("././Resources/Description.txt"); //Set your path here
	if (m_file.is_open())
	{
		while (std::getline(m_file, m_line))
		{
			std::shared_ptr<sf::Text> m_descriptionText = std::make_shared<sf::Text>(sf::Text());
			m_descriptionText->setFont(m_helpFont);
			m_descriptionText->setCharacterSize(25);
			m_descriptionText->setFillColor(sf::Color::White);
			//Getting every line of the .txt file and putting it in the 'line' string
			m_descriptionText->setString(m_line);
			m_textList.push_back(m_descriptionText);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
SceneHelp::~SceneHelp()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SceneHelp::isButtonClicked(int x_pos, int y_pos)
{
	if (x_pos >= 0 && x_pos <= m_width
		&& y_pos >= 0 && y_pos <= m_hight)
	{
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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

	float i = 0;
	float descriptionText_x = 0;
	for(auto& text : m_textList)
	{
		sf::FloatRect boundings = text->getLocalBounds();
		descriptionText_x = 1000 / 2 - m_width / 2 + (m_width - text->getLocalBounds().width) / 2;

		text->setPosition(descriptionText_x, m_button.getGlobalBounds().height + 40 + i * (boundings.height + 5));
		++i;

		target.draw(*text, states);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------