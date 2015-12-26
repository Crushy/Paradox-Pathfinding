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
	struct CandidateRecord {

		GridLocation coordinate;
		int costSoFar;
		int estimatedTotalCost;

		bool operator< (const CandidateRecord& other) const
		{
			return estimatedTotalCost > other.estimatedTotalCost;
		}
	};

	struct VisitedRecord {
		GridLocation coordinate;
		GridLocation previous;
		int costSoFar;
	};

	PathFinder(const SquareGrid& gridRef);
	~PathFinder();
	using HeurFn = int(GridLocation, GridLocation);

	std::list<GridLocation>* Pathfind(GridLocation entry, GridLocation goal, HeurFn heurist_func);
	
	const SquareGrid& grid;

	std::unordered_map<typename GridLocation, VisitedRecord, GridLocation::hash_GridLocation>* visited;

private:
	

	
};

