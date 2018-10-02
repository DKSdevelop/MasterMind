#include "ScenePlayGame.hpp"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
ScenePlayGame::ScenePlayGame(std::shared_ptr<GameModel> gameModel)
	:	m_gameModelPtr(gameModel),
		m_currentRow(&gameModel->getGameBoard().getCurrentRow()),
		m_selectedPlace(-1, -1),
		m_selectedColour(0)
{
	initialize();
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
	if (returnedVal.y != *m_currentRow)
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
bool ScenePlayGame::isRowOfColoursFilled()
{
	for (auto& ball : m_selectedBalls)
	{
		if (ball->getFillColor() == sf::Color::Black)
		{
			return false;
		}
	}
	return true;;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::clearPlaceAndColours()
{
	m_selectedPlace.x = -1;
	m_selectedPlace.y = -1;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::pushColourToRow()
{
	m_selectedBalls.at(m_selectedPlace.x)->setFillColor(m_ballsColours.at(m_selectedColour));
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<int> ScenePlayGame::getRowOfColour()
{
	std::vector<int> returnRow;

	for (auto& ball : m_selectedBalls)
	{
		unsigned int colourNum = std::find(m_ballsColours.begin(), m_ballsColours.end(), ball->getFillColor()) - m_ballsColours.begin();
		if (colourNum < m_ballsColours.size())
		{
			returnRow.push_back(colourNum);
		}
	}

	return returnRow;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::initialize()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//MAIN GRILL
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

			std::shared_ptr<sf::CircleShape> pastBall = std::make_shared<sf::CircleShape>(static_cast<float>(baseR));

			pastBall->setFillColor(sf::Color::Transparent);
			pastBall->setOrigin(0.f, 0.f);

			pastBall->setPosition(sf::Vector2f(x + baseR / 4, y + baseR / 4));

			m_pastBallsRows[i].push_back(pastBall);
			m_mainPlaces[i].push_back(sf::Vector2f(x, y));
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SCORED GRILL
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
			float y = m_scoreGrill.getGlobalBounds().top + (index * m_scoreGrill.getSize().y / (m_numOfRows * 2)) + baseThickness;

			std::shared_ptr<sf::RectangleShape> scoreField = std::make_shared<sf::RectangleShape>(
				sf::Vector2f((m_scoreGrill.getSize().x /2) - baseThickness - 1,
				(m_scoreGrill.getSize().y/24) - baseThickness - 1));

			scoreField->setFillColor(sf::Color::Transparent);
			scoreField->setOrigin(0.f, 0.f);

			scoreField->setPosition(sf::Vector2f(x + 1, y + 1));

			m_scoreRectangles[i].push_back(scoreField);
		}
		for (int j = 0; j < 2; ++j)
		{
			float x = m_scoreGrill.getGlobalBounds().left + (j * m_scoreGrill.getSize().x / 2) + baseThickness;
			float y = m_scoreGrill.getGlobalBounds().top + ((index + 1) * m_scoreGrill.getSize().y / (m_numOfRows * 2)) + baseThickness;

			std::shared_ptr<sf::RectangleShape> scoreField = std::make_shared<sf::RectangleShape>(
				sf::Vector2f((m_scoreGrill.getSize().x / 2) - baseThickness - 1,
				(m_scoreGrill.getSize().y / 24) - baseThickness - 1));

			scoreField->setFillColor(sf::Color::Transparent);
			scoreField->setOrigin(0.f, 0.f);

			scoreField->setPosition(sf::Vector2f(x + 1, y + 1));

			m_scoreRectangles[i].push_back(scoreField);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//COLOUR GRILL
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//INTERNAL GRILL LINES
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 1; i < m_numOfRows; ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseWidth), static_cast<float>(baseThickness)));
		line.setPosition(sf::Vector2f(static_cast<float>(basePositionX), static_cast<float>(m_mainGrill.getGlobalBounds().top + (i * m_mainGrill.getSize().y / m_numOfRows))));
		m_internalGrillLines.push_back(line);
	}

	for (int i = 1; i < 4; ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseThickness), static_cast<float>(baseHigh)));
		line.setPosition(sf::Vector2f(static_cast<float>(m_mainGrill.getGlobalBounds().left + (i * m_mainGrill.getSize().x / 4)), static_cast<float>(basePositionY)));
		m_internalGrillLines.push_back(line);
	}

	for (int i = 1; i < (m_numOfRows * 2); ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseWidth / 4), static_cast<float>(baseThickness)));
		line.setPosition(sf::Vector2f(static_cast<float>(basePositionX + baseWidth + 10), static_cast<float>(m_scoreGrill.getGlobalBounds().top + (i * m_scoreGrill.getSize().y / (m_numOfRows * 2)))));
		m_internalGrillLines.push_back(line);
	}

	for (int i = 1; i < 2; ++i)
	{
		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseThickness), static_cast<float>(baseHigh)));
		line.setPosition(sf::Vector2f(static_cast<float>(m_scoreGrill.getGlobalBounds().left + (i * m_scoreGrill.getSize().x / 2)), static_cast<float>(basePositionY)));
		m_internalGrillLines.push_back(line);
	}
	for (unsigned i = 0; i < m_colorsToChoosePlaces.size(); ++i)
	{
		float x = (float)(m_colorsToChoosePlaces.at(i).begin_x);
		float y = (float)(m_colorsToChoosePlaces.at(i).begin_y);


		sf::RectangleShape line(sf::Vector2f(static_cast<float>(baseThickness), static_cast<float>(baseWidth / 4)));
		line.setPosition(sf::Vector2f(x, y));
		m_internalGrillLines.push_back(line);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//COLORS BALLS
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (unsigned i = 0; i < m_colorsToChoosePlaces.size(); ++i)
	{
		float x = (float)(m_colorsToChoosePlaces.at(i).begin_x);
		float y = (float)(m_colorsToChoosePlaces.at(i).begin_y);

		sf::CircleShape coloredPeg(static_cast<float>(baseR));
		coloredPeg.setFillColor(m_ballsColours.at(i));
		coloredPeg.setOrigin(0.f, 0.f);
		coloredPeg.setPosition(sf::Vector2f(x + baseR / 4, y + baseR / 4));
		m_coloursBalls.push_back(coloredPeg);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//BUTTON
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float buttonWidth = m_choseGrill.getSize().x / 3;
	float buttonHigh = m_choseGrill.getSize().y;

	m_checkButton.setSize(sf::Vector2f(buttonWidth, buttonHigh));
	m_checkButton.setFillColor(sf::Color::Black);
	m_checkButton.setOutlineThickness(2);
	m_checkButton.setOutlineColor(sf::Color::White);
	m_checkButton.setFillColor(sf::Color(89, 89, 89));
	m_checkButton.setPosition(sf::Vector2f(m_choseGrill.getGlobalBounds().left + m_choseGrill.getGlobalBounds().width + 10, m_choseGrill.getGlobalBounds().top));


	m_buttonText.setFont(m_font);
	m_buttonText.setCharacterSize(20);
	m_buttonText.setFillColor(sf::Color::White);
	m_buttonText.setString("Check");

	float textBegin_x = m_checkButton.getGlobalBounds().left + (buttonWidth - m_buttonText.getLocalBounds().width) / 2;
	float textBegin_y = m_checkButton.getGlobalBounds().top + (buttonHigh - m_buttonText.getLocalBounds().height) / 2;

	m_buttonText.setPosition(textBegin_x, textBegin_y);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//COLOUR MARKER
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_colourMarker = std::make_shared<sf::RectangleShape>(sf::RectangleShape());
	m_colourMarker->setSize(sf::Vector2f(m_choseGrill.getSize().x / 6, m_choseGrill.getSize().y));
	m_colourMarker->setFillColor(sf::Color::Transparent);
	m_colourMarker->setOutlineThickness(static_cast<float>(baseThickness + 1));
	m_colourMarker->setOutlineColor(sf::Color::Yellow);

	float markerPositionX = m_colorsToChoosePlaces.at(m_selectedColour).begin_x;
	float markerPositionY = m_colorsToChoosePlaces.at(m_selectedColour).begin_y;
	m_colourMarker->setPosition(sf::Vector2f(markerPositionX, markerPositionY));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CURRENT ROW MARKER
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_currentRowMarker = std::make_shared<sf::RectangleShape>(sf::RectangleShape());
	m_currentRowMarker->setSize(sf::Vector2f(static_cast<float>(baseWidth), static_cast<float>(baseHigh / 12)));
	m_currentRowMarker->setFillColor(sf::Color::Transparent);
	m_currentRowMarker->setOutlineThickness(static_cast<float>(baseThickness + 1));
	m_currentRowMarker->setOutlineColor(sf::Color::Yellow);

	float positionX = m_mainPlaces.at(*m_currentRow).at(0).x;
	float positionY = m_mainPlaces.at(*m_currentRow).at(0).y;
	m_currentRowMarker->setPosition(sf::Vector2f(positionX, positionY));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	clearColourBallsRow();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::importScoreRow()
{
	auto scoreRow = m_gameModelPtr->getGameBoard().getVecOfPegRows().at((*m_currentRow) - 1).getVecOfKeyPegs();

	for(unsigned i = 0; i < scoreRow.size(); ++i)
	{
		int colornumber = scoreRow.at(i).getPegColor();
		if (colornumber < 8)
		{
			m_scoreRectangles[(*m_currentRow) - 1].at(i)->setFillColor(m_ballsColours.at(colornumber));
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::importPastRow()
{
	auto scoreRow = m_gameModelPtr->getGameBoard().getVecOfPegRows().at((*m_currentRow) - 1).getVecOfCodePegs();

	for(unsigned i = 0; i < scoreRow.size(); ++i)
	{
		int colornumber = scoreRow.at(i).getPegColor();
		if (colornumber <= 5)
		{
			m_pastBallsRows[(*m_currentRow) - 1].at(i)->setFillColor(m_ballsColours.at(colornumber));
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::clearColourBallsRow()
{
	if (!m_selectedBalls.empty())
	{
		m_selectedBalls.clear();
	}
	for (int i = 0; i < 4; ++i)
	{
		std::shared_ptr<sf::CircleShape> coloredPeg = std::make_shared<sf::CircleShape>(sf::CircleShape(static_cast<float>(baseR)));
		coloredPeg->setFillColor(m_ballsColours.at(8));
		coloredPeg->setOrigin(0.f, 0.f);

		float xPosition = m_mainPlaces.at(*m_currentRow).at(i).x;
		float yPosition = m_mainPlaces.at(*m_currentRow).at(i).y;

		coloredPeg->setPosition(sf::Vector2f(xPosition + baseR / 4, yPosition + baseR / 4));
		m_selectedBalls.push_back(coloredPeg);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScenePlayGame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	////////////////////////////////////////////////////////////////////////////////////
	//MAIN GRILL
	////////////////////////////////////////////////////////////////////////////////////
	target.draw(m_mainGrill, states);
	////////////////////////////////////////////////////////////////////////////////////
	//SCORE GRILL
	////////////////////////////////////////////////////////////////////////////////////
	target.draw(m_scoreGrill, states);
	////////////////////////////////////////////////////////////////////////////////////
	//COLOURS GRILL
	////////////////////////////////////////////////////////////////////////////////////
	target.draw(m_choseGrill, states);
	////////////////////////////////////////////////////////////////////////////////////
	//GRILL INTERNAL LINES
	////////////////////////////////////////////////////////////////////////////////////
	for (auto& line : m_internalGrillLines)
	{
		target.draw(line, states);
	}
	////////////////////////////////////////////////////////////////////////////////////
	//COLOUR BALLS
	////////////////////////////////////////////////////////////////////////////////////
	for (auto& ball : m_coloursBalls)
	{
		target.draw(ball, states);
	}
	////////////////////////////////////////////////////////////////////////////////////
	//COLOUR MARKER
	////////////////////////////////////////////////////////////////////////////////////
	float markerPositionX = m_colorsToChoosePlaces.at(m_selectedColour).begin_x;
	float markerPositionY = m_colorsToChoosePlaces.at(m_selectedColour).begin_y;
	m_colourMarker->setPosition(sf::Vector2f(markerPositionX, markerPositionY));
	target.draw(*m_colourMarker, states);
	////////////////////////////////////////////////////////////////////////////////////
	//CHECK BUTTON
	////////////////////////////////////////////////////////////////////////////////////
	target.draw(m_checkButton, states);
	target.draw(m_buttonText, states);
	////////////////////////////////////////////////////////////////////////////////////
	//PAST ROWS WITH BALLS
	////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < *m_currentRow; ++i)
	{
		for (auto& pastBall : m_pastBallsRows.at(i))
		{
			target.draw(*pastBall, states);
		}

	}
	////////////////////////////////////////////////////////////////////////////////////
	//SCORE ROWS WITH RESULTS
	////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < *m_currentRow; ++i)
	{
		for (auto& score : m_scoreRectangles.at(i))
		{
			target.draw(*score, states);
		}

	}
	////////////////////////////////////////////////////////////////////////////////////
	//CURRENT ROW MARKER
	////////////////////////////////////////////////////////////////////////////////////
	float positionX = m_mainPlaces.at(*m_currentRow).at(0).x;
	float positionY = m_mainPlaces.at(*m_currentRow).at(0).y;
	m_currentRowMarker->setPosition(sf::Vector2f(positionX, positionY));

	target.draw(*m_currentRowMarker, states);
	////////////////////////////////////////////////////////////////////////////////////
	//CURRENT ROW COLOUR BALLS
	////////////////////////////////////////////////////////////////////////////////////
	for (unsigned i = 0; i < m_selectedBalls.size(); ++i)
	{
		float xPosition = m_mainPlaces.at(*m_currentRow).at(i).x;
		float yPosition = m_mainPlaces.at(*m_currentRow).at(i).y;

		m_selectedBalls.at(i)->setPosition(sf::Vector2f(xPosition + baseR / 4, yPosition + baseR / 4));
		target.draw(*m_selectedBalls.at(i), states);
	}

	////////////////////////////////////////////////////////////////////////////////////
	//KEY ROW COLOUR BALLS (only for testing)
	////////////////////////////////////////////////////////////////////////////////////
	/*for (int i = 0; i < m_selectedBalls.size(); ++i)
	{
		auto ball = m_gameModelPtr->getGameBoard().getVecOfPegsInShield().at(i);
		int colornumber = ball.getPegColor();
		if (colornumber != -1)
		{
			sf::CircleShape coloredPeg(baseR);
			coloredPeg.setFillColor(m_ballsColours.at(colornumber));
			coloredPeg.setOrigin(0.f, 0.f);

			float xPosition = 0 + i* m_choseGrill.getSize().x/6;
			float yPosition = 0;

			coloredPeg.setPosition(sf::Vector2f(xPosition + baseR / 4, yPosition + baseR / 4));
			target.draw(coloredPeg, states);
		}
	}*/
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------