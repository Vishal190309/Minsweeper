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
		startText();
	}
	void Board::startText()
	{
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "|                            |\n";
		cout << "|    WELCOME TO MINESWEEPR   |\n";
		cout << "|                            |\n";
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		cout <<
			" RULES:\n"
			"1. The board is divided into cells, with mines distributed.\n"
			"2. To win, you need to open all the cells.\n"
			"3. The number on a cell shows the no of mines adjacent to it.Using this you can determine cells that are safe,"
			"and cell that contains mines"
			"4. Interact, evolve and enjoy\n\n"
			" How to Play :\n"
			"1. user will input x & y(coordinates where they want to click).\n"
			"2. In each step check win or lose case.\n";

		chekIfStartGame();

	}
	void Board::chekIfStartGame()
	{
		cout << "\nEnter Y/y to continue or N/n to quit\n";
		char c;
		cin >> c;
		if (c == 'y' || c == 'Y') {
			startGame();
		}
		else if (c == 'n' || c == 'N') {
			exit(0);
		}
		else {
			chekIfStartGame();
		}
	}
	void Board::startGame()
	{
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "|                            |\n";
		cout << "|         Game Starts        |\n";
		cout << "|                            |\n";
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;

		printBoard();

	}
	void Board::printBoard()
	{
		for (int i = 0; i < 17; i++) {
			cout << "-";
		}
		cout << endl;
		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				if (board[x][y]->getCellState() == Cell::CellState::HIDDEN) {
					cout << "| ";
				}
				else {
					cout << "|";
					if (board[x][y]->getCellValue() == Cell::CellValue::MINE) {
						cout << "*";
					}
					else {
						cout << static_cast<int>(board[x][y]->getCellValue());
					}
				}
				
			};
			cout << endl;
		}
		for (int i = 0; i < 17; i++) {
			cout << "-";
		}
		cout << endl<<endl;
	}
	void Board::openCell(int x, int y ,bool print  )
	{
		if (!isValidCellPosition(x, y)) {
			if (print) {
				cout << "Enterd Position is not valid\n";
			}
			return;
		}
		if (board[x][y]->getCellState() != Cell::CellState::OPEN) {
			if (boardState == BoardState::FIRST_CELL) {
				populateBoard(x, y);
				boardState = BoardState::PLAYING;

			}

			processCellVaue(x, y);
			board[x][y]->openCell();
			if (areAllCellOpen()) {
				gameWon();
			}
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

			if (board[xPos][yPos]->getCellValue() == Cell::CellValue::MINE || (xPos == x && yPos == y))i--;
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
		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				board[x][y]->openCell();
			};
		}
	}

	void Board::opneEmptyCell(int xPos, int yPos) {
		if (board[xPos][yPos]->getCellState() != Cell::CellState::OPEN) {
			board[xPos ][yPos]->openCell();
		}
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if ((x == 0 && y == 0) || !isValidCellPosition(xPos + x, yPos + y)) continue;
				openCell(xPos + x, yPos + y);
			}
		}
	}

	void Board::processCellVaue(int x, int y) {
		
		switch (board[x][y]->getCellValue())
		{
		case Cell::CellValue::EMPTY:
			processEmptyCell( x,  y);
			break;
		case Cell::CellValue::MINE:
			processMineCell( x,  y);
			break;
		default:
			break;
		}
	}

	void Board::processEmptyCell(int x, int y) {
		opneEmptyCell(x, y);
	}

	void Board::processMineCell(int x, int y) {
		gameLost();
	}

	bool Board::areAllCellOpen() {
		int totalCell = boardSize * boardSize;
		int openCell = 0;
		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				if (board[x][y]->getCellState() == Cell::CellState::OPEN) {
					openCell++;
				}
			};
		}

		return (openCell == totalCell - numberOfMines);
		
	}

	void Board::gameWon() {
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "|                            |\n";
		cout << "|           YOU WON          |\n";
		cout << "|                            |\n";
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		boardState = BoardState::COMPLETED;
		openAllCells();
		printBoard();
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "|                            |\n";
		cout << "|         GAME ENDS          |\n";
		cout << "|      SEE YOU NEXT TIME     |\n";
		cout << "|                            |\n";
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}

	}

	void Board::gameLost() {
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "|                                    |\n";
		cout << "|   OOPS! YOU STEPPED ON THE MINE    |\n";
		cout << "|            YOU LOSE                |\n";
		cout << "|                                    |\n";
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		boardState = BoardState::COMPLETED;
		openAllCells();
		printBoard();
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
		cout << endl;
		cout << "|                            |\n";
		cout << "|         GAME ENDS          |\n";
		cout << "|      SEE YOU NEXT TIME     |\n";
		cout << "|                            |\n";
		for (int i = 0; i < 30; i++) {
			cout << "-";
		}
	}

	BoardState Board::getBoardState()
	{
		return boardState;
	}
}