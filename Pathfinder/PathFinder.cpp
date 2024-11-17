#include "PathFinder.h"
#include <queue>
#include <unordered_map>
#include "Utils.hpp"

bool PathFinder::CandidateRecord::operator<(const CandidateRecord& other) const noexcept
{
	return other.estimated_total_cost < estimated_total_cost;
}

PathFinder::PathFinder(const grid::SquareGrid&& grid_ref):
	_grid(grid_ref)
{
}

bool PathFinder::find_path(const grid::GridLocation& entry, const grid::GridLocation& goal, heur_fn heuristic_func, std::list<grid::GridLocation>& results)
{
	results.clear();

	if (heuristic_func == nullptr) {
		return false;
	}

	// Can't reach start or destination
	if (_grid.get_element(goal) == IMPASSABLE || _grid.get_element(entry) == IMPASSABLE) {
		return false;
	}

	std::vector<grid::GridLocation> neighbours = std::vector<grid::GridLocation>(grid::SquareGrid::max_neighbours);

	visited.clear();// = new std::unordered_map<GridLocation, VisitedRecord, GridLocation::hash_GridLocation>();

	std::priority_queue<CandidateRecord> candidates;

	CandidateRecord start_record = CandidateRecord
	{
		goal,
		0,
		(1.0f + 0.001f) * heuristic_func(entry, goal)
	};

	candidates.emplace(start_record);
	
	while (!candidates.empty()) {
		CandidateRecord current_node = candidates.top();

		if (current_node.coordinate == entry)
		{
			break;
		}
		else
		{
			candidates.pop();
			neighbours.clear();

			//std::cout << "Visiting " << currentNode.coordinate << std::endl;
			_grid.get_neighbours(current_node.coordinate, neighbours);

			for (auto& neighbour : neighbours) {
				//Don't consider impassable positions
				if (_grid.get_element(neighbour) == IMPASSABLE) {
					continue;
				}
				
				const float costToNext = current_node.cost_so_far + MOVE_COST; //It always costs 1 to move to the neighbour coordinate

				//If we weren't visited yet or the current path takes less than a previous approach to this node
				if (visited.count(neighbour) <= 0) {
					auto& neighbour_rec = visited[neighbour];
					neighbour_rec.cost_so_far = costToNext;
					neighbour_rec.previous = current_node.coordinate;
					CandidateRecord new_record = CandidateRecord
					{
						neighbour,
						costToNext,
						costToNext + heuristic_func(neighbour, entry) * (1.0f + 0.001f)
					};

					candidates.emplace(new_record);
				}
				//We found a better path for this node
				else if (costToNext < visited[neighbour].cost_so_far) {
					auto& neighbour_rec = visited[neighbour];
					neighbour_rec.cost_so_far = costToNext;
					neighbour_rec.previous = current_node.coordinate;
					
					// Check if we already had this candidate to avoid going in circles
					// Commented out because travel costs are never 0, therefore there is no risk of having an infinite loop
					/*auto& it = candidates.find(newRecord);
					if (it != candidates.end() && (*it).costSoFar < newRecord.costSoFar ) {
						candidates.erase(it);
					*/
					
					/*for (auto& candidate : candidates) {
						if (candidate.coordinate == neighbour && candidate.costSoFar < costToNext) {
							candidates.erase(candidate);
						}
					}*/
					CandidateRecord new_record = CandidateRecord
					{
						neighbour,
						costToNext,
						costToNext + heuristic_func(neighbour, entry) * (1.0f + 0.001f)
					};

					//Better candidates are prioritized here based on the CandidateRecord "<" operator overload
					candidates.emplace(new_record);
					
						
				}
				//std::cout << "Visiting neighbour " << neighbour.x << " " << neighbour.y << std::endl;
			}

		}

	}

	if (candidates.empty()) {
		return false;
	}
	
	//Get Results
	{
		grid::GridLocation aux = entry;
		
		while (aux != goal) {
			aux = visited[aux].previous;
			results.emplace_back(aux);
		}
	}
	return true;
}