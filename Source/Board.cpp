#include "../Header/Board.h"
#include <iostream>
using namespace std;
namespace Board {
	int Board::countMinesAround(int xPos, int yPos)
	{
		int mineCount = 0;
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if((x ==0 && y==0) || !isValidCellPosition(xPos+x,yPos+y)) continue;
				if (board[xPos+x][yPos+y]->getCellValue() == Cell::CellValue::MINE) {
					mineCount++;
				}
			}
		}
		return mineCount;
	}
	bool Board::isValidCellPosition(int x ,int y)
	{
		return x >=0 && y>=0 && x < boardSize && y<boardSize;
	}
	Board::Board() : random_engine(random_device())
	{
		initialize();
	}
	Board::~Board()
	{
		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				delete board[x][y];
			};
		}
	}
	void Board::initialize()
	{
		boardState = BoardState::FIRST_CELL;

		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				board[x][y] = new Cell::Cell();
			};
		}
	}
	void Board::printBoard()
	{
		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				if (board[x][y]->getCellState() == Cell::CellState::HIDDEN) {
					cout << "| ";
				}
				else {
					cout << "|";
					cout << static_cast<int>(board[x][y]->getCellValue());
				}
				
			};
			cout << endl;
		}
	}
	void Board::openCell( int x, int y)
	{
		if (!isValidCellPosition(x, y)) {
			cout << "Enterd Position is not valid\n";
			return;
		}
			switch (boardState)
			{
			case BoardState::FIRST_CELL:
				populateBoard(x, y);
				board[x][y]->openCell();
				boardState = BoardState::PLAYING;
				printBoard();
				break;
			case BoardState::PLAYING:
				board[x][y]->openCell();
				printBoard();
				break;
			case BoardState::COMPLETED:
				break;
			default:
				break;
			}
		
		
	}
	void Board::populateBoard(int x , int y)
	{
		populateMines(x, y);
		populateCells();
	}

	void Board::populateMines(int x, int y) {
		std::uniform_int_distribution<int> xDistribution(0, boardSize - 1);
		std::uniform_int_distribution<int> yDistribution(0, boardSize - 1);

		for (int i = 0; i < numberOfMines; i++) {
			int xPos = static_cast<int>(xDistribution(random_engine));
			int yPos = static_cast<int>(yDistribution(random_engine));

			if (board[xPos][yPos]->getCellValue() == Cell::CellValue::MINE || (xPos = x && yPos == y))i--;
			else board[xPos][yPos]->setCellValue(Cell::CellValue::MINE);
		}
	}

	void Board::populateCells() {
		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				if (board[x][y]->getCellValue() != Cell::CellValue::MINE) {
					board[x][y]->setCellValue(static_cast<Cell::CellValue>(countMinesAround(x, y)));
				}
			};
		}
	}
	void Board::openAllCells()
	{
	}
	BoardState Board::getBoardState()
	{
		return boardState;
	}
}