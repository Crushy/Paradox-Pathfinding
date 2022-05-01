#pragma once
#include "SquareGrid.hpp"
#include <unordered_map>

using namespace Grid;

class PathFinder
{
public:
	struct CandidateRecord {

		GridLocation coordinate;
		int costSoFar;
		float estimatedTotalCost;

		bool operator< (const CandidateRecord& other) const noexcept
		{
			return other.estimatedTotalCost < estimatedTotalCost;
		}
	};

	struct VisitedRecord {
		GridLocation previous;
		int costSoFar = 0;
	};

	PathFinder(const SquareGrid& gridRef);
	using HeurFn = int(const GridLocation&, const GridLocation&);

	bool Pathfind(const GridLocation entry, const GridLocation goal, HeurFn heurist_func, std::list<GridLocation>& results);
	
	const SquareGrid& grid;

	std::unordered_map<typename GridLocation, VisitedRecord, GridLocation::hash_GridLocation> visited;

private:

};

