#pragma once
#include <iostream>
#include "SquareGrid.hpp"

int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize) {

	SquareGrid gridData = SquareGrid(pMap, nMapWidth, nMapHeight);

	for (int i = 0; i < gridData.height(); i++)
	{
		for (int j = 0; j < gridData.width(); j++)
		{
			std::cout << gridData.GetElement(j, i) + 1;
		}

		std::cout << std::endl;
	}

	gridData.Pathfind(SquareGrid::GridLocation(nStartX, nStartY), SquareGrid::GridLocation(nTargetX, nTargetY));


	return 0;
}

auto main() {
	//Init Pathfinding
	

	SquareGrid::GridLocation entry = SquareGrid::GridLocation(0, 0);
	SquareGrid::GridLocation goal = SquareGrid::GridLocation(1, 2);

	//Example 1
	unsigned char pMap1[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer1[12];
	FindPath(0, 0, 1, 2, pMap1, 4, 3, pOutBuffer1, 12);

	std::cout << "#############" << std::endl;

	//Example 2
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[7];
	FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);

	

	return;
}
