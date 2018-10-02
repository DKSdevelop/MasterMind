#pragma once
#include <string>

#include "../DrawableGroup.hpp"
#include "../../Model/GameModel.hpp"

class SceneEndGame : public DrawableGroup
{
private:
	std::shared_ptr<GameModel> m_gameModelPtr;

	bool m_winGame;
	bool m_playAgain;

	int m_width;
	int m_hight;
	int m_x;
	int m_y;

	sf::RectangleShape m_buttonPlayAgain;
	sf::RectangleShape m_buttonExit;

	sf::Text textPlayAgain;
	sf::Text textExit;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	SceneEndGame(std::shared_ptr<GameModel> gameModel);
	~SceneEndGame();

	bool isButtonClicked(int x_pos, int y_pos);
	void setGameScore(bool score);
	bool wantPlayAgain();
};

