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

	public:
		Board();
		~Board();


		// To generate random values.
		std::default_random_engine random_engine;

		// To give random seed to generator.
		std::random_device random_device;


		void initialize();
		void printBoard();
		void openCell(int x, int y);
		void populateBoard(int x, int y);
		void populateMines(int x, int y);
		void populateCells();
		void openAllCells();

		BoardState getBoardState();
	};
}