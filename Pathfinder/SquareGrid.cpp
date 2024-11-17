#include "SquareGrid.h"

namespace grid
{
    SquareGrid::SquareGrid(const unsigned char* grid, const int width, const int height) noexcept
    {
        this->_grid = grid;

        this->_width = width;
        this->_height = height;

        return;
    }

    inline const GridValue& SquareGrid::get_element(const int x, const int y) const noexcept
    {
        return this->_grid[coordinates_2d_to_array(x, y, this->_width)];
    }

    const GridValue& SquareGrid::get_element(const GridLocation& loc) const noexcept
    {
        return get_element(loc.x, loc.y);
    }

    void SquareGrid::get_neighbours(GridLocation coord, std::vector<GridLocation>& to_fill) const
    {
        //North
        if (coord.y > 0)
        {
            to_fill.emplace_back(coord.x, coord.y - 1);
        }
        //West
        if (coord.x > 0)
        {
            to_fill.emplace_back(coord.x - 1, coord.y);
        }
        //East
        if (coord.x < this->_width - 1)
        {
            to_fill.emplace_back(coord.x + 1, coord.y);
        }
        //South
        if (coord.y < this->_height - 1)
        {
            to_fill.emplace_back(coord.x, coord.y + 1);
        }
    }
}