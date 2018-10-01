#pragma once
#include "DrawableGroup.hpp"
#include "GameModel.hpp"


class SceneMainMenu : public DrawableGroup
{
public:
	SceneMainMenu(std::shared_ptr<GameModel> gameModel);
	~SceneMainMenu();

	int checkWhichButton(int x_pos, int y_pos);
private:
	std::shared_ptr<GameModel> m_gameModelPtr;
	sf::Font m_font;

	std::vector<std::string> m_options{
		"Start Game",
		"Help",
		"Exit"
	};

	std::vector<sf::Vector2i> m_coords;

	int m_x;
	int m_y;
	int m_width;
	int m_hight;
	int m_separator;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

