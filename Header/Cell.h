#pragma once

namespace Cell {
    enum class CellState
    {
        HIDDEN,
        OPEN,
    };

    enum class CellValue
    {
        EMPTY,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        MINE,
    };

	class Cell {
	private:
        CellState cellState;
        CellValue cellValue;

    public:
        Cell();
        ~Cell();

        void openCell();
        void setCellValue(CellValue value);

        CellState getCellState();
        CellValue getCellValue();


	};
}