// Minsweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Header/Board.h"
using namespace std;



int main()
{   
    
    Board::Board* board = new Board::Board();

    while (board->getBoardState() != Board::BoardState::COMPLETED) {
        cout << "Enter x and y co-ordinates:\n";
        int x;
        int y;
        cin >> y>>x;

        board->openCell(x, y,true);
        if (board->getBoardState() != Board::BoardState::COMPLETED) {
            board->printBoard();
        }
    }
    
}

