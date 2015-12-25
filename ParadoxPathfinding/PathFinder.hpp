#pragma once
#include "SquareGrid.hpp"
#include <queue>
#include <array>
#include <unordered_map>
#include "Utils.hpp"

using namespace Grid;

class PathFinder
{
public:
	PathFinder(const SquareGrid& gridRef);
	~PathFinder();
	using HeurFn = int(GridLocation, GridLocation);

	//TODO: fix the magic number
	std::list<GridLocation>* Pathfind(GridLocation entry, GridLocation goal, HeurFn heurist_func);
	
	const SquareGrid& grid;

private:
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

	struct VisitedRecord {

		GridLocation node;
		GridLocation previous;
		int costSoFar;
	};

	
};

