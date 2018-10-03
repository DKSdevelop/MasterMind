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
		float i = 0;
		float descriptionText_x = 0;
		while (std::getline(m_file, m_line))
		{
			std::shared_ptr<sf::Text> m_descriptionText = std::make_shared<sf::Text>(sf::Text());
			m_descriptionText->setFont(m_helpFont);
			m_descriptionText->setCharacterSize(25);
			m_descriptionText->setFillColor(sf::Color::White);
			//Getting every line of the .txt file and putting it in the 'line' string
			m_descriptionText->setString(m_line);
			sf::FloatRect boundings = m_descriptionText->getLocalBounds();
			descriptionText_x = 1000 / 2 - m_width / 2 + (m_width - m_descriptionText->getLocalBounds().width) / 2;

			m_descriptionText->setPosition(descriptionText_x, m_hight + 40 + i * (boundings.height + 5));
			++i;
			m_textList.push_back(m_descriptionText);
		}
	}

	m_texture.loadFromFile("././Resources/Example2.JPG");

	m_example = std::make_shared<sf::Sprite>(sf::Sprite(m_texture));
	auto positionOfSprint = m_textList.back()->getPosition();
	positionOfSprint.y += 50;
	m_example->setPosition(positionOfSprint);
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

	for(auto& text : m_textList)
	{
		target.draw(*text, states);
	}

	target.draw(*m_example, states);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------