#include "SquareGrid.hpp"


SquareGrid::SquareGrid() {
	this->grid = nullptr;
	this->_width = 0;
	this->_height = 0;
}

SquareGrid::SquareGrid(const unsigned char* grid, const int width, const int height) {

	this->grid = grid;

	this->_width = width;
	this->_height = height;

	return;
}

SquareGrid::~SquareGrid()
{
}


GridValue SquareGrid::GetElement(int x, int y) {
	return this->grid[Coordinates2DToArray(x, y, this->_width)];
}

GridValue SquareGrid::GetElement(GridLocation loc) {
	return GetElement(loc.x, loc.y);
}

void SquareGrid::GetNeighbours(GridLocation coord, std::vector<GridLocation>& toFill) {

	//North
	if (coord.y > 0) {
		toFill.push_back(GridLocation(coord.x, coord.y - 1));
	}
	//West
	if (coord.x > 0) {
		toFill.push_back(GridLocation(coord.x - 1, coord.y));
	}
	//East
	if (coord.x < this->_width - 1) {
		toFill.push_back(GridLocation(coord.x + 1, coord.y));
	}
	//South
	if (coord.y < this->_height - 1) {
		toFill.push_back(GridLocation(coord.x, coord.y + 1));
	}
	/*
	for (std::vector<GridItem>::const_iterator j = toFill.begin(); j != toFill.end(); ++j)
	{
	std::cout << coord << (*j) << std::endl;
	}*/

}


void SquareGrid::Pathfind(GridLocation entry, GridLocation goal)
{
	std::priority_queue<CandidateRecord> candidates;
	std::unordered_map<typename GridLocation, VisitedRecord, GridLocation::hash_GridLocation> visited;

	CandidateRecord startRecord = CandidateRecord
	{
		entry,
		GridLocation(-1,-1),
		0,
		heuristic(entry,goal)
	};

	candidates.push(startRecord);

	std::vector<GridLocation> toFill = std::vector<GridLocation>(max_neighbours);

	while (candidates.size() > 0) {
		CandidateRecord currentNode = candidates.top();


		if (currentNode.node == goal) { //Found the goal, exit
			std::cout << "done" << std::endl;
			break;
		}
		else {
			candidates.pop();

			toFill.clear();
			GetNeighbours(currentNode.node, toFill);
			std::cout << "visiting" << std::endl;

			for (auto next : toFill) {
				int costToNext = currentNode.costSoFar + 1; //It always costs 1 to move to the next node
				if (GetElement(next) == Impassable) {
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
						costToNext + heuristic(next, goal)
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
		std::cout << Coordinates2DToArray(aux.node.x, aux.node.y, _width) << std::endl;
		//std::cout << (aux.node) << std::endl;
		aux = visited[aux.previous];
	} while (aux.node != entry);


	return;
}

//Getters
const int SquareGrid::width()
{
	return _width;
}

const int SquareGrid::height()
{
	return _height;
}

//Estimate distance between nodes
inline int SquareGrid::heuristic(SquareGrid::GridLocation a, SquareGrid::GridLocation b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

