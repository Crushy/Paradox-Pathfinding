#include "SquareGrid.hpp"

namespace Grid {
	SquareGrid::SquareGrid() {
		this->grid = nullptr;
		this->_width = 0;
		this->_height = 0;
	}

	SquareGrid::SquareGrid(const unsigned char* grid, const int width, const int height) {

		this->grid = grid;

		this->_width = width;
		this->_height = height;

		return;
	}

	SquareGrid::~SquareGrid()
	{
	}

	GridValue SquareGrid::GetElement(int x, int y) const
	{
		return this->grid[Coordinates2DToArray(x, y, this->_width)];
	}

	void SquareGrid::GetNeighbours(GridLocation coord, std::vector<GridLocation>& toFill) const
	{

		//North
		if (coord.y > 0) {
			toFill.push_back(GridLocation(coord.x, coord.y - 1));
		}
		//West
		if (coord.x > 0) {
			toFill.push_back(GridLocation(coord.x - 1, coord.y));
		}
		//East
		if (coord.x < this->_width - 1) {
			toFill.push_back(GridLocation(coord.x + 1, coord.y));
		}
		//South
		if (coord.y < this->_height - 1) {
			toFill.push_back(GridLocation(coord.x, coord.y + 1));
		}
		/*
		for (std::vector<GridItem>::const_iterator j = toFill.begin(); j != toFill.end(); ++j)
		{
		std::cout << coord << (*j) << std::endl;
		}*/

	}
}