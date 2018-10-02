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

	sf::Vector2i m_selectedPlace;
	int m_selectedColour;
	std::vector<int> m_rowOfColours;

	std::map<int, std::vector<sf::Vector2f>> m_mainPlaces;
	std::map<int, std::vector<sf::Vector2f>> m_scorePlaces;

	std::vector<RectanglePlace> m_colorsToChoosePlaces;

	const int m_numOfRows = 12;
	const int baseWidth = 200;
	const int baseHigh = 600;
	const int basePositionX = 250;
	const int basePositionY = 150;
	const int baseThickness = 2;
	const int baseR = baseWidth / 10;

	std::vector<sf::Color> _playColors{
		sf::Color::Red,
		sf::Color::Yellow,
		sf::Color::Green,
		sf::Color(255, 153, 0),
		sf::Color(204, 51, 255),
		sf::Color::Blue,
		sf::Color::Cyan,
		sf::Color::Green
	};

	sf::RectangleShape m_mainGrill;
	sf::RectangleShape m_scoreGrill;
	sf::RectangleShape m_choseGrill;

	sf::RectangleShape m_checkButton;
	sf::Text buttonText;
//-----------------------------------------------------------------------------
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
	void chnageSelectedColour(int x_pos);
	bool isRowOfColoursFilled();

	void clearPlaceAndColours();
	void clearRowOfColours();

	void pushColourToRow();
	std::vector<int> getRowOfColour();
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};

