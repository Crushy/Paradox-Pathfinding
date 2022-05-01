#pragma once

#define TRAVERSABLE 1
#define IMPASSABLE  0
typedef unsigned char GridValue;

#include <iostream>
#include <vector>

namespace Grid {

	/*
	A 2D grid location
	*/
	struct GridLocation {
		int x = 0;
		int y = 0;

		struct hash_GridLocation {
			size_t operator()(const GridLocation &location) const noexcept {
				return std::hash<int>()(location.x) ^ std::hash<int>()(location.y);
			}
		};

		GridLocation() noexcept {
			this->x = 0;
			this->y = 0;
		}

		GridLocation(unsigned int x, unsigned int y) noexcept {
			this->x = x;
			this->y = y;
		}

		inline bool operator== (const GridLocation &other) const noexcept {
			return (this->x == other.x && this->y == other.y);
		}

		inline bool operator!= (const GridLocation &other) const noexcept {
			return (this->x != other.x || this->y != other.y);
		}

		friend std::ostream &operator<<(std::ostream &os, GridLocation const &ourselves) {
			return os << "GridLocation(" << ourselves.x << " , " << ourselves.y << ")";
		}
	};

	/*
	A square grid. Ideally should implement a Generic Grid interface.
	*/
	class SquareGrid
	{
	public:
		//Consts
		static const int max_neighbours = 4;

		const inline int Coordinates2DToArray(int x, int y, int width) const noexcept
		{
			return width*y + x;
		}

		const inline GridLocation CoordinatesArrayTo2D(int i, int width) const noexcept
		{
			return GridLocation(i % width, i / width);
		}

		//Constructors
		SquareGrid(const unsigned char* grid, const int width, const int height) noexcept {

			this->_grid = grid;

			this->_width = width;
			this->_height = height;

			return;
		}

#pragma warning( disable : 26481) //Surpress warning to use span instead of pointer math

		//Method declarations
		inline GridValue GetElement(int x, int y) const noexcept
		{
			return this->_grid[Coordinates2DToArray(x, y, this->_width)];
		}

#pragma warning( default : 26481)

		inline GridValue GetElement(GridLocation loc) const noexcept
		{
			return GetElement(loc.x, loc.y);
		}

		void GetNeighbours(GridLocation coord, std::vector<GridLocation>& toFill) const
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

		//Getters
		const inline int width() const noexcept {
			return _width;
		}

		const inline int height() const noexcept {
			return _height;
		}

		inline void ToConsole() const {
			//std::cout << _height << std::endl;

			for (int i = 0; i < _height; i++)
			{
				for (int j = 0; j < _width; j++)
				{
					std::cout << GetElement(j, i) + 1;
				}

				std::cout << std::endl;
			}
		}

	private:
		int _width = 0;
		int _height = 0;
		const GridValue* _grid; //Ideally this should be using array_view but GLSL is not allowed
	};

}