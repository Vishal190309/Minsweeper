#include "../Header/Cell.h"

namespace Cell {
	Cell::Cell()
	{
		cellState = CellState::HIDDEN;
		cellValue = CellValue::EMPTY;
	}
	Cell::~Cell()
	{
	}
	void Cell::openCell()
	{
		cellState = CellState::OPEN;
	}
	void Cell::setCellValue(CellValue value)
	{
		cellValue = value;
	}
	CellState Cell::getCellState()
	{
		return cellState;
	}
	CellValue Cell::getCellValue()
	{
		return cellValue;
	}
}