#pragma once
#include "GameElements\Board.h"
#include "GameElements\Subject.h"
#include <memory>

class GameModel : public Subject
{
private:
	int m_rowCount;
	int m_pegsInRow;
	Board m_gameBoard;
public:
	GameModel(int rowCount, int pegsInRow);
	virtual ~GameModel() {}
	Board & getGameBoard();
	void startGame();
	void initGame();
	int getPegsInRow() const;
	int getRowCount() const;
};

