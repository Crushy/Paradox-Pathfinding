#pragma once
#include "SquareGrid.hpp"
#include <queue>
#include <unordered_map>
#include "Utils.hpp"

using namespace Grid;

class PathFinder
{
public:
	PathFinder(const SquareGrid& gridRef);
	~PathFinder();
	using HeurFn = int(GridLocation, GridLocation);
	void Pathfind(GridLocation entry, GridLocation goal, HeurFn heurist_func);
	
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

