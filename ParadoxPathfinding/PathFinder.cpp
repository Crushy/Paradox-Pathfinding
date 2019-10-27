#include "PathFinder.hpp"

PathFinder::PathFinder(const SquareGrid& gridRef):
	grid(gridRef)
{

}

PathFinder::~PathFinder()
{
	std::cout << "Destroying pathfinder"<<std::endl;
}

std::list<GridLocation>* PathFinder::Pathfind(GridLocation entry, GridLocation goal, HeurFn heurist_func)
{
	if (entry == goal) {
		return 0;
	}

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
		

		if (currentNode.coordinate == goal)
		{
			break;
		}
		else 
		{
			candidates.pop();
			neighbours.clear();

			//std::cout << "Visiting " << currentNode.coordinate << std::endl;
			grid.GetNeighbours(currentNode.coordinate, neighbours);
			

			for (auto neighbour : neighbours) {
				//Don't consider impassable positions
				if (grid.GetElement(neighbour) == Impassable) {
					continue;
				}

				int costToNext = currentNode.costSoFar + 1; //It always costs 1 to move to the neighbour coordinate
				
				//If we aren't a visitor yet or the current path takes less than a previous approach to this node
				if (visited->count(neighbour) <= 0 || costToNext < (*visited)[neighbour].costSoFar) {
					(*visited)[neighbour].costSoFar = costToNext;
					(*visited)[neighbour].coordinate = neighbour;
					(*visited)[neighbour].previous = currentNode.coordinate;
					
					CandidateRecord newRecord = CandidateRecord
					{
						neighbour,
						costToNext,
						costToNext + heurist_func(neighbour, goal)
					};

					//Better candidates are prioritized here based on the CandidateRecord "<" operator overload
					candidates.push(newRecord);
				}
				//std::cout << "Visiting neighbour " << neighbour.x << " " << neighbour.y << std::endl;
			}

		}

	}

	std::list<GridLocation>* results = new std::list<GridLocation>();

	if (candidates.size() <= 0) {
		return results;
	}

	//Reverse
	GridLocation aux = goal;
	//std::cout << "Goal is " << aux << std::endl;
	
	do {
		results->push_front(aux);
		//std::cout << "Going back through " << aux << std::endl;
		aux = (*visited)[aux].previous;
		
	} while (aux != entry);

	return results;
}