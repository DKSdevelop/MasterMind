#include "ScenePlayGame.hpp"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
ScenePlayGame::ScenePlayGame(std::shared_ptr<GameModel> gameModel)
	:	m_gameModelPtr(gameModel),
		m_selectedPlace(-1, -1),
		m_selectedColour(0),
		m_rowOfColours(4,-1)
{
	///CHOSE MAIN GRILL
	m_mainGrill.setSize(sf::Vector2f(static_cast<float>(baseWidth), static_cast<float>(baseHigh)));
	m_mainGrill.setFillColor(sf::Color::Black);
	m_mainGrill.setOutlineThickness(static_cast<float>(baseThickness));
	m_mainGrill.setOutlineColor(sf::Color::White);
	m_mainGrill.setPosition(sf::Vector2f(static_cast<float>(basePositionX), static_cast<float>(basePositionY)));

	for (int i = 0; i < m_numOfRows; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float x = m_mainGrill.getGlobalBounds().left + (j * m_mainGrill.getSize().x / 4);
			float y = m_mainGrill.getGlobalBounds().top + (i * m_mainGrill.getSize().y / m_numOfRows);

			m_mainPlaces[i].push_back(sf::Vector2f(x,y));
		}
	}
	///
	///CHOSE SCORED GRILL
	m_scoreGrill.setSize(sf::Vector2f(static_cast<float>(baseWidth / 4), static_cast<float>(baseHigh)));
	m_scoreGrill.setFillColor(sf::Color::Black);
	m_scoreGrill.setOutlineThickness(static_cast<float>(baseThickness));
	m_scoreGrill.setOutlineColor(sf::Color::White);
	m_scoreGrill.setPosition(sf::Vector2f(static_cast<float>(basePositionX + baseWidth + 10), static_cast<float>(basePositionY)));

	for (int i = 0; i < m_numOfRows; ++i)
	{
		int index = i * 2;
		for (int j = 0; j < 2; ++j)
		{
			float x = m_scoreGrill.getGlobalBounds().left + (j * m_scoreGrill.getSize().x / 2) + baseThickness;
			float y = m_scoreGrill.getGlobalBounds().top + (index * m_scoreGrill.getSize().y / (m_numOfRows*2)) + baseThickness;
			m_scorePlaces[i].push_back(sf::Vector2f(x, y));
		}
		for (int j = 0; j < 2; ++j)
		{
			float x = m_scoreGrill.getGlobalBounds().left + (j * m_scoreGrill.getSize().x / 2) + baseThickness;
			float y = m_scoreGrill.getGlobalBounds().top + ((index +1) * m_scoreGrill.getSize().y / (m_numOfRows * 2)) + baseThickness;
			m_scorePlaces[i].push_back(sf::Vector2f(x, y));
		}
	}
	///
	///CHOSE COLOUR GRILL
	m_choseGrill.setSize(sf::Vector2f(static_cast<float>(baseWidth + baseWidth / 2), static_cast<float>(baseHigh / m_numOfRows)));
	m_choseGrill.setFillColor(sf::Color::Black);
	m_choseGrill.setOutlineThickness(static_cast<float>(baseThickness));
	m_choseGrill.setOutlineColor(sf::Color::White);
	m_choseGrill.setPosition(sf::Vector2f(static_cast<float>(basePositionX), static_cast<float>(basePositionY + baseHigh + 25)));
	///CHOSE COLOUR GRILL (coords of places)
	for (int i = 0; i < 6; ++i)
	{
		float x = m_choseGrill.getGlobalBounds().left + (i * m_choseGrill.getSize().x / 6);
		float y = static_cast<float>(basePositionY + baseHigh + 25);
		m_colorsToChoosePlaces.push_back({ x, y, x + m_choseGrill.getSize().x / 6, y + m_choseGrill.getSize().x / 6 });
	}
	///BUTTON
	float buttonWidth = m_choseGrill.getSize().x / 3;
	float buttonHigh = m_choseGrill.getSize().y;

	m_checkButton.setSize(sf::Vector2f(buttonWidth, buttonHigh));
	m_checkButton.setFillColor(sf::Color::Black);
	m_checkButton.setOutlineThickness(2);
	m_checkButton.setOutlineColor(sf::Color::White);
	m_checkButton.setFillColor(sf::Color(89, 89, 89));
	m_checkButton.setPosition(sf::Vector2f(m_choseGrill.getGlobalBounds().left + m_choseGrill.getGlobalBounds().width + 10, m_choseGrill.getGlobalBounds().top));


	buttonText.setFont(m_font);
	buttonText.setCharacterSize(20);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setString("Check");

	float textBegin_x = m_checkButton.getGlobalBounds().left + (buttonWidth - buttonText.getLocalBounds().width) / 2;
	float textBegin_y = m_checkButton.getGlobalBounds().top + (buttonHigh - buttonText.getLocalBounds().height) / 2;

	buttonText.setPosition(textBegin_x, textBegin_y);
	///
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
ScenePlayGame::~ScenePlayGame()
{
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::setSelectedColour(int x_pos)
{
	int xPosOnGrill = static_cast<int>(x_pos - m_choseGrill.getGlobalBounds().left);
	int sizeOfOnePlace = static_cast<int>(m_choseGrill.getGlobalBounds().width / 6);
	int returnedColour = xPosOnGrill / sizeOfOnePlace;
	m_selectedColour = returnedColour;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::setSelectedPosition(int x_pos, int y_pos)
{
	sf::Vector2i returnedVal;

	int yPosOnGrill = static_cast<int>(y_pos - m_mainGrill.getGlobalBounds().top);
	returnedVal.y = static_cast<int>(yPosOnGrill / (m_mainGrill.getGlobalBounds().height / 12));
	if (returnedVal.y != m_gameModelPtr->getGameBoard().getCurrentRow())
	{
		m_selectedPlace = sf::Vector2i(-1, -1);
	}
	else
	{
		int xPosOnGrill = static_cast<int>(x_pos - m_mainGrill.getGlobalBounds().left);
		returnedVal.x = static_cast<int>(xPosOnGrill / (m_mainGrill.getGlobalBounds().width / 4));

		m_selectedPlace = returnedVal;
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScenePlayGame::isMainGrill(int x_pos, int y_pos)
{
	if (x_pos >= m_mainGrill.getGlobalBounds().left && x_pos <= m_mainGrill.getGlobalBounds().left + m_mainGrill.getGlobalBounds().width
		&& y_pos >= m_mainGrill.getGlobalBounds().top && y_pos <= m_mainGrill.getGlobalBounds().top + m_mainGrill.getGlobalBounds().height)
	{
		setSelectedPosition(x_pos, y_pos);
		return true;
	}
		
	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScenePlayGame::isColourGrill(int x_pos, int y_pos)
{
	if (x_pos >= m_choseGrill.getGlobalBounds().left && x_pos <= m_choseGrill.getGlobalBounds().left + m_choseGrill.getGlobalBounds().width
		&& y_pos >= m_choseGrill.getGlobalBounds().top && y_pos <= m_choseGrill.getGlobalBounds().top + m_choseGrill.getGlobalBounds().height)
	{
		return true;
	}

	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScenePlayGame::isButtonClicked(int x_pos, int y_pos)
{
	if (x_pos >= m_checkButton.getGlobalBounds().left && x_pos <= m_checkButton.getGlobalBounds().left + m_checkButton.getGlobalBounds().width
		&& y_pos >= m_checkButton.getGlobalBounds().top && y_pos <= m_checkButton.getGlobalBounds().top + m_checkButton.getGlobalBounds().height)
	{
		return true;
	}

	return false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScenePlayGame::isPlaceSelected()
{
	return m_selectedPlace.x != -1 && m_selectedPlace.y != -1;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::chnageSelectedColour(int x_pos)
{
	setSelectedColour(x_pos);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScenePlayGame::isRowOfColoursFilled()
{
	auto result = std::find(std::begin(m_rowOfColours), std::end(m_rowOfColours), -1);
	return result == m_rowOfColours.end();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::clearPlaceAndColours()
{
	m_selectedPlace.x = -1;
	m_selectedPlace.y = -1;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::clearRowOfColours()
{
	std::fill(m_rowOfColours.begin(), m_rowOfColours.end(), -1);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::pushColourToRow()
{
	m_rowOfColours.at(m_selectedPlace.x) = m_selectedColour;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<int> ScenePlayGame::getRowOfColour()
{
	return m_rowOfColours;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_mainGrill, states);

	for (int i = 1; i < m_numOfRows; ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseWidth), static_cast<float>(baseThickness)));
		line.setPosition(sf::Vector2f(static_cast<float>(basePositionX), static_cast<float>(m_mainGrill.getGlobalBounds().top + (i * m_mainGrill.getSize().y / m_numOfRows))));
		target.draw(line, states);
	}

	for (int i = 1; i < 4; ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseThickness), static_cast<float>(baseHigh)));
		line.setPosition(sf::Vector2f(static_cast<float>(m_mainGrill.getGlobalBounds().left + (i * m_mainGrill.getSize().x / 4)), static_cast<float>(basePositionY)));
		target.draw(line, states);
	}

	target.draw(m_scoreGrill, states);

	for (int i = 1; i < (m_numOfRows * 2); ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseWidth / 4), static_cast<float>(baseThickness)));
		line.setPosition(sf::Vector2f(static_cast<float>(basePositionX + baseWidth + 10), static_cast<float>(m_scoreGrill.getGlobalBounds().top + (i * m_scoreGrill.getSize().y / (m_numOfRows * 2)))));
		target.draw(line, states);
	}

	for (int i = 1; i < 2; ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseThickness), static_cast<float>(baseHigh)));
		line.setPosition(sf::Vector2f(static_cast<float>(m_scoreGrill.getGlobalBounds().left + (i * m_scoreGrill.getSize().x / 2)), static_cast<float>(basePositionY)));
		target.draw(line, states);
	}

	target.draw(m_choseGrill, states);

	int i = 0;
	for(auto& pos : m_colorsToChoosePlaces)
	{
		float x = (float)(pos.begin_x);
		float y = (float)(pos.begin_y);


		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseThickness), static_cast<float>(baseWidth / 4)));
		line.setPosition(sf::Vector2f(x, y));
		target.draw(line, states);

		sf::CircleShape coloredPeg(static_cast<float>(baseR));
		coloredPeg.setFillColor(_playColors.at(i++));
		coloredPeg.setOrigin(0.f, 0.f);
		coloredPeg.setPosition(sf::Vector2f(x + baseR / 4, y + baseR / 4));
		target.draw(coloredPeg, states);
	}
	//COLOUR MARKER
	sf::RectangleShape colourMarker;
	colourMarker.setSize(sf::Vector2f(m_choseGrill.getSize().x / 6, m_choseGrill.getSize().y));
	colourMarker.setFillColor(sf::Color::Transparent);
	colourMarker.setOutlineThickness(static_cast<float>(baseThickness + 1));
	colourMarker.setOutlineColor(sf::Color::Yellow);
	float markerPositionX = m_colorsToChoosePlaces.at(m_selectedColour).begin_x;
	float markerPositionY = m_colorsToChoosePlaces.at(m_selectedColour).begin_y;
	colourMarker.setPosition(sf::Vector2f(markerPositionX, markerPositionY));
	target.draw(colourMarker, states);

	target.draw(m_checkButton, states);
	target.draw(buttonText, states);

	//printing existing rows with balls
	for (int i = 0; i < m_gameModelPtr->getGameBoard().getCurrentRow(); ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			Peg ball = m_gameModelPtr->getGameBoard().getVecOfPegRows().at(i).getVecOfCodePegs().at(j);
			int colornumber = ball.getPegColor();
			if(colornumber <= 5)
			{
				sf::CircleShape coloredPeg(static_cast<float>(baseR));
				coloredPeg.setFillColor(_playColors.at(colornumber));
				coloredPeg.setOrigin(0.f, 0.f);

				float xPosition = m_mainPlaces.at(i).at(j).x;
				float yPosition = m_mainPlaces.at(i).at(j).y;

				coloredPeg.setPosition(sf::Vector2f(xPosition + baseR / 4, yPosition + baseR / 4));
				target.draw(coloredPeg, states);
			}
		}
		
	}
	//printing score rows
	for (int i = 0; i < m_gameModelPtr->getGameBoard().getCurrentRow(); ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Peg score = m_gameModelPtr->getGameBoard().getVecOfPegRows().at(i).getVecOfKeyPegs().at(j);
			int colornumber = score.getPegColor();
			if (colornumber < 8)
			{
				sf::RectangleShape scoreField(sf::Vector2f((m_scoreGrill.getSize().x/2)- baseThickness -1, (m_scoreGrill.getSize().y/24)- baseThickness - 1));
				scoreField.setFillColor(_playColors.at(colornumber));
				scoreField.setOrigin(0.f, 0.f);

				float xPosition = m_scorePlaces.at(i).at(j).x;
				float yPosition = m_scorePlaces.at(i).at(j).y;

				scoreField.setPosition(sf::Vector2f(xPosition+1, yPosition+1));
				target.draw(scoreField, states);
			}
		}

	}
	//printing marker
	sf::RectangleShape marker;
	marker.setSize(sf::Vector2f(static_cast<float>(baseWidth), static_cast<float>(baseHigh/12)));
	marker.setFillColor(sf::Color::Transparent);
	marker.setOutlineThickness(static_cast<float>(baseThickness + 1));
	marker.setOutlineColor(sf::Color::Yellow);
	float positionX = m_mainPlaces.at(m_gameModelPtr->getGameBoard().getCurrentRow()).at(0).x;
	float positionY = m_mainPlaces.at(m_gameModelPtr->getGameBoard().getCurrentRow()).at(0).y;
	marker.setPosition(sf::Vector2f(positionX, positionY));

	target.draw(marker, states);

	//printing current row with balls
	for(unsigned i = 0; i < m_rowOfColours.size(); ++i)
	{
		int ball = m_rowOfColours.at(i);
		if (ball != -1)
		{
			sf::CircleShape coloredPeg(static_cast<float>(baseR));
			coloredPeg.setFillColor(_playColors.at(ball));
			coloredPeg.setOrigin(0.f, 0.f);

			float xPosition = m_mainPlaces.at(m_gameModelPtr->getGameBoard().getCurrentRow()).at(i).x;
			float yPosition = m_mainPlaces.at(m_gameModelPtr->getGameBoard().getCurrentRow()).at(i).y;

			coloredPeg.setPosition(sf::Vector2f(xPosition + baseR / 4, yPosition + baseR / 4));
			target.draw(coloredPeg, states);
		}
	}

	//printing key
	/*for (int i = 0; i < m_rowOfColours.size(); ++i)
	{
		auto ball = m_gameModelPtr->getGameBoard().getVecOfPegsInShield().at(i);
		int colornumber = ball.getPegColor();
		if (colornumber != -1)
		{
			sf::CircleShape coloredPeg(baseR);
			coloredPeg.setFillColor(_playColors.at(colornumber));
			coloredPeg.setOrigin(0.f, 0.f);

			float xPosition = 0 + i* m_choseGrill.getSize().x/6;
			float yPosition = 0;

			coloredPeg.setPosition(sf::Vector2f(xPosition + baseR / 4, yPosition + baseR / 4));
			target.draw(coloredPeg, states);
		}
	}*/
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------