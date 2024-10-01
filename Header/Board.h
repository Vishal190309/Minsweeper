#pragma once
#include "Cell.h"
#include <array>
#include <random>
namespace Board {

	enum class BoardState
	{
		FIRST_CELL,      
		PLAYING,         
		COMPLETED,    
	};
	class Board {
	private:
		static const int boardSize = 9;
		static const int numberOfMines = 8;


		Cell::Cell* board[boardSize][boardSize];

		BoardState boardState;

		int countMinesAround(int xPos, int yPos);
		bool isValidCellPosition(int x, int y);
		void populateBoard(int x, int y);
		void populateMines(int x, int y);
		void populateCells();
		void openAllCells();
		void opneEmptyCell(int x, int y);
		void processCellVaue(int x, int y);
		void processEmptyCell(int x, int y);
		void processMineCell(int x, int y);
		bool areAllCellOpen();
		void gameWon();
		void gameLost();
		void initialize();

		void startText();
		void chekIfStartGame();
		void startGame();
		
	public:
		Board();
		~Board();


		// To generate random values.
		std::default_random_engine random_engine;

		// To give random seed to generator.
		std::random_device random_device;


		void openCell(int x, int y, bool print = false);
		void printBoard();

		BoardState getBoardState();
	};
}