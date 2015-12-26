#include "PathFinder.hpp"

PathFinder::PathFinder(const SquareGrid& gridRef):
	grid(gridRef)
{

}

PathFinder::~PathFinder()
{
	std::cout << "We are gone :("<<std::endl;
}

std::list<GridLocation>* PathFinder::Pathfind(GridLocation entry, GridLocation goal, HeurFn heurist_func)
{
	std::vector<GridLocation> neighbours = std::vector<GridLocation>(grid.max_neighbours);

	visited = new std::unordered_map<typename GridLocation, VisitedRecord, GridLocation::hash_GridLocation>();

	std::priority_queue<CandidateRecord> candidates;
	

	CandidateRecord startRecord = CandidateRecord
	{
		entry,
		0,
		heurist_func(entry,goal)
	};

	candidates.push(startRecord);

	
	CandidateRecord currentNode = startRecord;
	while (candidates.size() > 0) {
		currentNode = candidates.top();
		candidates.pop();

		if (currentNode.coordinate == goal)
		{
			break;
		}
		{
			neighbours.clear();

			std::cout << "Visiting " << currentNode.coordinate << std::endl;
			grid.GetNeighbours(currentNode.coordinate, neighbours);
			

			for (auto neighbour : neighbours) {
				int costToNext = currentNode.costSoFar + 1; //It always costs 1 to move to the neighbour coordinate
				if (grid.GetElement(neighbour) == Impassable) {
					continue;
				}
				else if (visited->count(neighbour) <= 0 || costToNext < (*visited)[neighbour].costSoFar) {
					(*visited)[neighbour].costSoFar = costToNext;
					(*visited)[neighbour].coordinate = neighbour;
					(*visited)[neighbour].previous = currentNode.coordinate;

					candidates.push(CandidateRecord
					{
						neighbour,
						costToNext,
						costToNext + heurist_func(neighbour, goal)
					}
					);
				}

			}

		}

	}

	std::list<GridLocation>* results = new std::list<GridLocation>();

	if (candidates.size() <= 0) {
		std::cout << -1 << std::endl;
		return results;
	}
	else {
		//visited[goal].previous = currentNode.coordinate;
	}

	//Reverse


	GridLocation aux = goal;

	
	do {
		results->push_back(aux);
		std::cout << "Going back through " << aux << std::endl;
		//std::cout << (aux.coordinate) << std::endl;
		aux = (*visited)[aux].previous;
		
	} while (aux != entry);

	return results;
}