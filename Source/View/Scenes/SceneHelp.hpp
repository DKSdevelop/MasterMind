#pragma once

#include "../DrawableGroup.hpp"
#include "../../Model/GameModel.hpp"

class SceneHelp : public DrawableGroup
{
public:
	SceneHelp(std::shared_ptr<GameModel> gameModel);
	~SceneHelp();

	bool isButtonClicked(int x_pos, int y_pos);
private:
	std::shared_ptr<GameModel> m_gameModelPtr;
	//sf::Font m_font;

	int m_width;
	int m_hight;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

