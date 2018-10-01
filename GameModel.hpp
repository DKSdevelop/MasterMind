#pragma once
#include "Board.h"
#include "Subject.h"
#include <memory>

class GameModel : public Subject
{
	int m_rowCount;
	int m_pegsInRow;
	Board m_gameBoard;
	//GameState m_state;
public:
	GameModel(int rowCount, int pegsInRow);
	virtual ~GameModel() {}
	Board & getGameBoard();
	void startGame();
	void initGame();
	//GameState getState() const;
	//void setState(GameState state);
	int getPegsInRow() const;
	int getRowCount() const;
};

