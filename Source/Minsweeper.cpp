// Minsweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Header/Board.h"
using namespace std;



int main()
{   
    
    Board::Board* board = new Board::Board();
    while (board->getBoardState() != Board::BoardState::COMPLETED) {
        int x;
        int y;
        cin >> x;
        cin >> y;

        board->openCell(x, y);
    }
}

