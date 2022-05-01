#pragma once
#include <iostream>
#include "PathFinder.hpp"
#include "UI/DisplayGridSFML.hpp"
#include "Utils.hpp"

//This is some fairly old school code so we have to disable a bunch of warnings
#pragma warning( disable : 26485 26481 26446 26429)

int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize) {

	const GridLocation start = Grid::GridLocation(nStartX, nStartY);
	const GridLocation target = Grid::GridLocation(nTargetX, nTargetY);

	if (start == target) {
		return 0;
	}

	const Grid::SquareGrid gridData = Grid::SquareGrid(pMap, nMapWidth, nMapHeight);

	PathFinder path(gridData);

	std::list<GridLocation> pathfound(nOutBufferSize);

	path.Pathfind(start, target, Utils::ManhattanDistance, pathfound);

	if (pathfound.size() < 1 || pathfound.back() != target) {
		return -1;
	}

	int i = 0;
	for (auto const& node : pathfound) {
		pOutBuffer[i++] = gridData.Coordinates2DToArray(node.x, node.y, nMapWidth);
	}

	
	return pathfound.size();
}

void PrintPath(const int* const pOutBuffer1, int length) {

	std::cout << "\tLength: " << length << std::endl;
	std::cout << "\tPath: ";
	//std::copy(std::begin(pOutBuffer1), std::end(pOutBuffer1), std::ostream_iterator<int>(std::cout, ", "));

	for (int i = 0; i < length; i++) {
		std::cout << pOutBuffer1[i] << ", ";
	}
	std::cout << std::endl;
}

int main() {
	//Init Pathfinding

	//Testing
	//const unsigned char clearmap[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	//
	const unsigned char pMap3[] = {
		1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1,
		1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0,
		1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1,
		1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1};

	/*const unsigned char pMap3[] = {
		0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0,
		0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1,
		0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1 };
		*/
	//int pOutBuffer3[100];
	//std::cout << "Example 3 Output:" << std::endl;
	//length = FindPath(0, 0, 8, 6, pMap3, 20, 10, pOutBuffer3, 100);
	//length = FindPath(0, 9, 1, 3, pMap3, 20, 10, pOutBuffer3, 100);
	//PrintPath(pOutBuffer3, length);
	//std::cout << "#############" << std::endl;
	
	//UI
	const Grid::SquareGrid testGrid = Grid::SquareGrid(pMap3, 20, 10);
	
	PathFinder pathfinder = PathFinder(testGrid);
	DisplayGridSFML disp(testGrid,pathfinder);
	disp.Run();

	return 0;
}

#pragma warning( default : 26485 26481 26446 26429)
