#pragma once
#include <vector>
#include <algorithm>

#include "../DrawableGroup.hpp"
#include "../../Model/GameModel.hpp"

struct RectanglePlace
{
	float begin_x;
	float begin_y;
	float end_x;
	float end_y;
};

class ScenePlayGame : public DrawableGroup
{
private:
//-----------------------------------------------------------------------------
	std::shared_ptr<GameModel> m_gameModelPtr;

	std::shared_ptr<int> m_currentRow;

	sf::Vector2i m_selectedPlace;
	int m_selectedColour;

	const int m_numOfRows = 12;
	const int baseWidth = 200;
	const int baseHigh = 600;
	const int basePositionX = 250;
	const int basePositionY = 150;
	const int baseThickness = 2;
	const int baseR = baseWidth / 10;

	std::vector<sf::Color> m_ballsColours
	{
		sf::Color::Red,
		sf::Color::Yellow,
		sf::Color::Green,
		sf::Color(255, 153, 0),
		sf::Color(204, 51, 255),
		sf::Color::Blue,
		sf::Color::Cyan,
		sf::Color::Green,
		sf::Color::Black
	};
	sf::RectangleShape m_mainGrill;
	sf::RectangleShape m_scoreGrill;
	sf::RectangleShape m_choseGrill;

	std::vector<sf::RectangleShape> m_internalGrillLines;

	sf::RectangleShape m_checkButton;
	sf::Text m_buttonText;

	std::map<int, std::vector<sf::Vector2f>> m_mainPlaces;
	//std::map<int, std::vector<sf::Vector2f>> m_scorePlaces;
	std::vector<RectanglePlace> m_colorsToChoosePlaces;

	std::vector<sf::CircleShape> m_coloursBalls;

	std::vector<std::shared_ptr<sf::CircleShape>> m_selectedBalls;

	std::map<int, std::vector<std::shared_ptr<sf::RectangleShape>>> m_scoreRectangles;
	std::map<int, std::vector<std::shared_ptr<sf::CircleShape>>> m_pastBallsRows;

	std::shared_ptr<sf::RectangleShape> m_colourMarker;
	std::shared_ptr<sf::RectangleShape> m_currentRowMarker;
//-----------------------------------------------------------------------------
	void initialize();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
public:
	//-----------------------------------------------------------------------------
	ScenePlayGame(std::shared_ptr<GameModel> gameModel);
	~ScenePlayGame();

	void setSelectedColour(int x_pos);
	void setSelectedPosition(int x_pos, int y_pos);

	bool isMainGrill(int x_pos, int y_pos);
	bool isColourGrill(int x_pos, int y_pos);
	bool isButtonClicked(int x_pos, int y_pos);

	bool isPlaceSelected();
	bool isRowOfColoursFilled();

	void clearPlaceAndColours();
	void clearColourBallsRow();

	void pushColourToRow();
	std::vector<int> getRowOfColour();
	void importScoreRow();
	void importPastRow();
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};

