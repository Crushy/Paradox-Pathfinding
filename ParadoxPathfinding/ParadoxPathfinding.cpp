#include "stdafx.h"

#include <iostream>

#include <queue>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <functional>

class GridData {

	public :
		typedef unsigned char GridValue;

		#define Traversable 1
		#define Impassable  0

		struct GridLocation {
			int x = 0;
			int y = 0;

			struct hash_GridLocation {
				size_t operator()(const GridLocation &location) const {
					return std::hash<int>()(location.x) ^ std::hash<int>()(location.y);
				}
			};

			GridLocation() {
				this->x = 0;
				this->y = 0;
			}

			GridLocation(unsigned int x, unsigned int y) {
				this->x = x;
				this->y = y;
			}

			bool operator== (const GridLocation &other) const {
				return (this->x == other.x && this->y == other.y);
			}

			bool operator!= (const GridLocation &other) const {
				return (this->x != other.x || this->y != other.y);
			}

			friend std::ostream &operator<<(std::ostream &os, GridLocation const &ourselves) {
				return os << "GridLocation(" << ourselves.x << " , " << ourselves.y << ")";
			}
		};
		
		
		GridValue GetElement(int x, int y) {
			return this->grid[Coordinates2DToArray(x, y, this->_width)];
		}

		GridValue GetElement(GridLocation loc) {
			return GetElement(loc.x,loc.y);
		}

		inline int Coordinates2DToArray(int x, int y, int width) {
			return width*y + x;
		}
		/*
		inline GridData::GridLocation CoordinatesArrayTo2D(int i, int width) {
			return GridData::GridLocation(i % width, i / width);
		}*/

		GridData(const unsigned char* grid, const int width, const int height) {

			this->grid = grid;

			this->_width = width;
			this->_height = height;

			return;
		}

		void GetNeighbours(GridLocation coord, std::vector<GridLocation>& toFill) {
			
			//North
			if (coord.y > 0) {
				toFill.push_back(GridLocation(coord.x, coord.y - 1));
			}
			//West
			if (coord.x > 0) {
				toFill.push_back(GridLocation(coord.x - 1, coord.y));
			}
			//East
			if (coord.x < this->_width-1) {
				toFill.push_back(GridLocation(coord.x + 1, coord.y));
			}
			//South
			if (coord.y < this->_height-1) {
				toFill.push_back(GridLocation(coord.x, coord.y + 1));
			}
			/*
			for (std::vector<GridItem>::const_iterator j = toFill.begin(); j != toFill.end(); ++j)
			{
				std::cout << coord << (*j) << std::endl;
			}*/

		}



		void Pathfind(GridLocation entry, GridLocation goal)
		{
			std::priority_queue<CandidateRecord> candidates;
			std::unordered_map<typename GridLocation, VisitedRecord,GridLocation::hash_GridLocation> visited;

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
					GetNeighbours(currentNode.node,toFill);
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
				std::cout << Coordinates2DToArray(aux.node.x,aux.node.y,_width) << std::endl;
				//std::cout << (aux.node) << std::endl;
				aux = visited[aux.previous];
			} while (aux.node != entry);
			

			return;
		}

		//Getters
		const int width()
		{
			return _width;
		}

		const int height()
		{
			return _height;
		}

	private :
		int _width = 0;
		int _height = 0;
		const GridValue* grid; //Ideally this should be using array_view but I have no idea if GLSL is allowed

		struct VisitedRecord {

			GridLocation node;
			GridLocation previous;
			int costSoFar;
		};

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

		//Estimate distance between nodes
		inline int heuristic(GridData::GridLocation a, GridData::GridLocation b) {
			return abs(a.x - b.x) + abs(a.y - b.y);
		}

		const int max_neighbours = 4;
	
};




float lerp(float value, float start, float end)
{
	return start + (end - start) * value;
}

int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize) {

	GridData gridData = GridData(pMap, nMapWidth, nMapHeight);

	for (int i = 0; i < gridData.height(); i++)
	{
		for (int j = 0; j < gridData.width(); j++)
		{
			std::cout << gridData.GetElement(j, i) + 1;
		}

		std::cout << std::endl;
	}

	gridData.Pathfind(GridData::GridLocation(nStartX,nStartY), GridData::GridLocation(nTargetX,nTargetY));


	return 0;
}



//Clamps from min (inclusive) to max (exclusive)
int clamp(int val, int min, int max) {
	int ret = std::min(val, max-1);
	ret = std::max(ret, min);
	return ret;
}


int main() {
	//Init Pathfinding
	

	GridData::GridLocation entry = GridData::GridLocation(0, 0);
	GridData::GridLocation goal = GridData::GridLocation(1, 2);

	//Example 1
	unsigned char pMap1[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer1[12];
	FindPath(0, 0, 1, 2, pMap1, 4, 3, pOutBuffer1, 12);

	std::cout << "#############" << std::endl;

	//Example 2
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[7];
	FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);

	

	return 0;
}
