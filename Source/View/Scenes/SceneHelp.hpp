#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "../DrawableGroup.hpp"
#include "../../Model/GameModel.hpp"

class SceneHelp : public DrawableGroup
{
private:
//-----------------------------------------------------------------------------
	std::shared_ptr<GameModel> m_gameModelPtr;

	int m_width;
	int m_hight;

	std::string m_line;
	std::ifstream m_file;
	std::list<std::shared_ptr<sf::Text>> m_textList;
//-----------------------------------------------------------------------------
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
public:
//-----------------------------------------------------------------------------
	SceneHelp(std::shared_ptr<GameModel> gameModel);
	~SceneHelp();

	bool isButtonClicked(int x_pos, int y_pos);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};

