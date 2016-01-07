#pragma once

#define Traversable 1
#define Impassable  0
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
			size_t operator()(const GridLocation &location) const {
				return std::hash<int>()(location.x) ^ std::hash<int>()(location.y);
			}
		};

		GridLocation() {
			this->x = 0;
			this->y = 0;
		}

		GridLocation(unsigned int x, unsigned int y) {
			this->x = x;
			this->y = y;
		}

		bool operator== (const GridLocation &other) const {
			return (this->x == other.x && this->y == other.y);
		}

		bool operator!= (const GridLocation &other) const {
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

		const inline int SquareGrid::Coordinates2DToArray(int x, int y, int width) const
		{
			return width*y + x;
		}

		const inline GridLocation SquareGrid::CoordinatesArrayTo2D(int i, int width) const
		{
			return GridLocation(i % width, i / width);
		}

		//Constructors,Destructors
		SquareGrid();
		SquareGrid(const unsigned char* grid, const int width, const int height);

		~SquareGrid();

		//Inlines

		//Method declarations
		GridValue SquareGrid::GetElement(int x, int y) const;
		inline GridValue GetElement(GridLocation loc) const
		{
			return GetElement(loc.x, loc.y);
		}
		void GetNeighbours(GridLocation coord, std::vector<GridLocation>& toFill) const;

		//Getters
		const int SquareGrid::width() const
		{
			return _width;
		}

		const int SquareGrid::height() const
		{
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
		const GridValue* grid; //Ideally this should be using array_view but GLSL is probably not allowed

	};


}