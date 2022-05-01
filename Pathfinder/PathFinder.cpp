#include "PathFinder.hpp"
#include <queue>
#include <set>
#include <unordered_map>
#include "Utils.hpp"

PathFinder::PathFinder(const SquareGrid& gridRef):
	grid(gridRef),
	visited()
{
}

bool PathFinder::Pathfind(const GridLocation entry, const GridLocation goal, HeurFn heurist_func, std::list<GridLocation>& results)
{
	results.clear();

	if (heurist_func == nullptr) {
		return false;
	}

	// Can't reach start or destination
	if (grid.GetElement(goal) == IMPASSABLE || grid.GetElement(entry) == IMPASSABLE) {
		return false;
	}

	std::vector<GridLocation> neighbours = std::vector<GridLocation>(grid.max_neighbours);

	visited.clear();// = new std::unordered_map<GridLocation, VisitedRecord, GridLocation::hash_GridLocation>();

	std::priority_queue<CandidateRecord> candidates;

	CandidateRecord startRecord = CandidateRecord
	{
		goal,
		0,
		heurist_func(entry,goal) * (1.0f + 0.001f)
	};

	candidates.emplace(startRecord);
	
	CandidateRecord currentNode = startRecord;
	//const CandidateRecord* pointer = nullptr;
	while (candidates.size() > 0) {
		currentNode = candidates.top();
		//pointer = &(*candidates.rbegin());

		if (currentNode.coordinate == entry)
		{
			break;
		}
		else
		{
			candidates.pop();
			neighbours.clear();

			//std::cout << "Visiting " << currentNode.coordinate << std::endl;
			grid.GetNeighbours(currentNode.coordinate, neighbours);

			for (auto& neighbour : neighbours) {
				//Don't consider impassable positions
				if (grid.GetElement(neighbour) == IMPASSABLE) {
					continue;
				}

				const int costToNext = currentNode.costSoFar + 1; //It always costs 1 to move to the neighbour coordinate

				//If we weren't visited yet or the current path takes less than a previous approach to this node
				if (visited.count(neighbour) <= 0) {
					auto& neighbourRec = visited[neighbour];
					neighbourRec.costSoFar = costToNext;
					neighbourRec.previous = currentNode.coordinate;
					CandidateRecord newRecord = CandidateRecord
					{
						neighbour,
						costToNext,
						costToNext + heurist_func(neighbour, entry) * (1.0f + 0.001f)
					};

					candidates.emplace(newRecord);
				}
				//We found a better path for this node
				else if (costToNext < visited[neighbour].costSoFar) {
					auto& neighbourRec = visited[neighbour];
					neighbourRec.costSoFar = costToNext;
					neighbourRec.previous = currentNode.coordinate;

					//Check if we already had this candidate
					//Commented out because travel costs are never 0
					/*auto& it = candidates.find(newRecord);
					if (it != candidates.end() && (*it).costSoFar < newRecord.costSoFar ) {
						candidates.erase(it);
					*/
					
					/*for (auto& candidate : candidates) {
						if (candidate.coordinate == neighbour && candidate.costSoFar < costToNext) {
							candidates.erase(candidate);
						}
					}*/
					CandidateRecord newRecord = CandidateRecord
					{
						neighbour,
						costToNext,
						costToNext + heurist_func(neighbour, entry) * (1.0f + 0.001f)
					};

					//Better candidates are prioritized here based on the CandidateRecord "<" operator overload
					candidates.emplace(newRecord);
					
						
				}
				//std::cout << "Visiting neighbour " << neighbour.x << " " << neighbour.y << std::endl;
			}

		}

	}

	if (candidates.size() <= 0) {
		return false;
	}
	
	//Get Results
	{
		GridLocation aux = entry;

		while (aux != goal) {
			aux = visited[aux].previous;
			results.push_back(aux);
		};
		//results->push_back(goal);
	}
	return true;
}