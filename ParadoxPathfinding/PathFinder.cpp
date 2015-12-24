#include "PathFinder.hpp"

PathFinder::PathFinder(const SquareGrid& gridRef):
	grid(gridRef)
{

}

PathFinder::~PathFinder()
{
	std::cout << "We are gone :("<<std::endl;
}

void PathFinder::Pathfind(GridLocation entry, GridLocation goal, HeurFn heurist_func)
{
	std::priority_queue<CandidateRecord> candidates;
	std::unordered_map<typename GridLocation, VisitedRecord, GridLocation::hash_GridLocation> visited;

	CandidateRecord startRecord = CandidateRecord
	{
		entry,
		GridLocation(-1,-1), //Just a random invalid coordinate
		0,
		heurist_func(entry,goal)
	};

	candidates.push(startRecord);

	std::vector<GridLocation> toFill = std::vector<GridLocation>(grid.max_neighbours);

	while (candidates.size() > 0) {
		CandidateRecord currentNode = candidates.top();


		if (currentNode.node == goal) { //Found the goal, exit
			std::cout << "done" << std::endl;
			break;
		}
		else {
			candidates.pop();

			toFill.clear();

			std::cout << "Visiting " << currentNode.node << std::endl;
			grid.GetNeighbours(currentNode.node, toFill);
			

			for (auto next : toFill) {
				int costToNext = currentNode.costSoFar + 1; //It always costs 1 to move to the next node
				if (grid.GetElement(next) == Impassable) {
					continue;
				}
				if (visited.count(next) <= 0 || costToNext < visited[next].costSoFar) {
					visited[next].costSoFar = costToNext;
					visited[next].node = next;
					visited[next].previous = currentNode.node;

					candidates.push(CandidateRecord
					{
						next,
						currentNode.node,
						costToNext,
						costToNext + heurist_func(next, goal)
					}
					);
				}

			}

		}

	}

	if (candidates.size() <= 0) {
		std::cout << -1 << std::endl;
		return;
	}

	//Reverse
	VisitedRecord aux = visited[goal];
	do {
		std::cout << grid.Coordinates2DToArray(aux.node.x, aux.node.y, grid.width()) << std::endl;
		//std::cout << (aux.node) << std::endl;
		aux = visited[aux.previous];
	} while (aux.node != entry);


	return;
}