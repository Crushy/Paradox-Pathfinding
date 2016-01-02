#pragma once
#include <iostream>
//#include "SquareGrid.hpp"
#include "PathFinder.hpp"
#include "DisplayGridSFML.hpp"


int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize) {

	Grid::SquareGrid gridData = Grid::SquareGrid(pMap, nMapWidth, nMapHeight);

	gridData.ToConsole();

	PathFinder path(gridData);
	path.Pathfind(Grid::GridLocation(nStartX, nStartY), Grid::GridLocation(nTargetX, nTargetY), Utils::ManhattanDistance);

	gridData.ToConsole();

	return 0;
}

auto main() {
	//Init Pathfinding
	
	/*
	Grid::GridLocation entry = Grid::GridLocation(0, 0);
	Grid::GridLocation goal = Grid::GridLocation(1, 2);

	//Example 1
	unsigned char pMap1[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer1[12];
	FindPath(0, 0, 1, 2, pMap1, 4, 3, pOutBuffer1, 12);

	std::cout << "#############" << std::endl;

	//Example 2
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[7];
	FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);
	*/
	//Testing
	unsigned char pMap3[] = { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1,
		0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1 };
	
	int pOutBuffer3[7];
	FindPath(4, 0, 0, 2, pMap3, 20, 10, pOutBuffer3, 7);

	Grid::SquareGrid& testGrid = Grid::SquareGrid(pMap3, 20, 10);
	PathFinder& pathfinder = PathFinder(testGrid);
	DisplayGridSFML disp(testGrid,pathfinder);
	disp.Run();
	return;
}
