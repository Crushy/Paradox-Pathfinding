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

	std::priority_queue<CandidateRecord> candidates;
	std::unordered_map<typename GridLocation, VisitedRecord, GridLocation::hash_GridLocation> visited;

	CandidateRecord startRecord = CandidateRecord
	{
		entry,
		GridLocation(-200,-200), //Just a random invalid coordinate
		0,
		heurist_func(entry,goal)
	};

	candidates.push(startRecord);

	

	while (candidates.size() > 0) {
		CandidateRecord currentNode = candidates.top();
		candidates.pop();

		if (currentNode.node == goal) { //Found the goal, exit
			std::cout << "done" << std::endl;
			break;
		}
		else {
			neighbours.clear();

			std::cout << "Visiting " << currentNode.node << std::endl;
			grid.GetNeighbours(currentNode.node, neighbours);
			

			for (auto neighbour : neighbours) {
				int costToNext = currentNode.costSoFar + 1; //It always costs 1 to move to the neighbour node
				if (grid.GetElement(neighbour) == Impassable) {
					continue;
				}
				else if (visited.count(neighbour) <= 0 || costToNext < visited[neighbour].costSoFar) {
					visited[neighbour].costSoFar = costToNext;
					visited[neighbour].node = neighbour;
					visited[neighbour].previous = currentNode.node;

					candidates.push(CandidateRecord
					{
						neighbour,
						currentNode.node,
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

	//Reverse
	VisitedRecord aux = visited[goal];
	do {
		results->push_back(aux.node);
		std::cout << "Going back through " << aux.node << std::endl;
		//std::cout << (aux.node) << std::endl;
		aux = visited[aux.previous];
		
	} while (aux.node != entry);


	return results;
}