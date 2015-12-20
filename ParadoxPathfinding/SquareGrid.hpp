#pragma once

#define Traversable 1
#define Impassable  0
typedef unsigned char GridValue;

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>


class SquareGrid
{
public:
	SquareGrid();
	SquareGrid(const unsigned char* grid, const int width, const int height);

	~SquareGrid();

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

	inline int SquareGrid::Coordinates2DToArray(int x, int y, int width)
	{
		return width*y + x;
	}

	inline SquareGrid::GridLocation SquareGrid::CoordinatesArrayTo2D(int i, int width)
	{
		return SquareGrid::GridLocation(i % width, i / width);
	}

	void Pathfind(GridLocation entry, GridLocation goal);

	GridValue SquareGrid::GetElement(int x, int y);
	GridValue SquareGrid::GetElement(GridLocation loc);

	inline int SquareGrid::heuristic(GridLocation a, GridLocation b);

	const int SquareGrid::width();
	const int SquareGrid::height();

	//template <> int heuristic_Function(GridLocation a, GridLocation b);

private:
	int _width = 0;
	int _height = 0;
	const GridValue* grid; //Ideally this should be using array_view but I have no idea if GLSL is allowed

	struct VisitedRecord {

		GridLocation node;
		GridLocation previous;
		int costSoFar;
	};

	struct CandidateRecord {

		GridLocation node;
		GridLocation previous;
		int costSoFar;
		int estimatedTotalCost;

		bool operator< (const CandidateRecord& other) const
		{
			return estimatedTotalCost > other.estimatedTotalCost;
		}
	};

	const int max_neighbours = 4;

	void GetNeighbours(GridLocation coord, std::vector<GridLocation>& toFill);

};


