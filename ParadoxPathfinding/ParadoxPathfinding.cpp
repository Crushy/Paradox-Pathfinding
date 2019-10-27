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

	//gridData.ToConsole();

	PathFinder path(gridData);
	std::list<GridLocation>* foundPath = path.Pathfind(Grid::GridLocation(nStartX, nStartY), Grid::GridLocation(nTargetX, nTargetY), Utils::ManhattanDistance);

	int i = 0;
	for (auto const& node : *foundPath) {
		//std::cout << i.x * i.y;
		pOutBuffer[i++] = gridData.Coordinates2DToArray(node.x, node.y, nMapWidth);
	}

	//gridData.ToConsole();

	return foundPath->size();
}

void PrintPath(int* pOutBuffer1, int length) {

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
	
	/*
	Grid::GridLocation entry = Grid::GridLocation(0, 0);
	Grid::GridLocation goal = Grid::GridLocation(1, 2);
	*/
	//Example 1
	unsigned char pMap1[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer1[12];
	int length = FindPath(0, 0, 1, 2, pMap1, 4, 3, pOutBuffer1, 12);

	std::cout << "Example 1 Output:" << std::endl;
	
	
	PrintPath(pOutBuffer1, length);
	std::cout << "#############" << std::endl;
	
	//Example 2
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[7];
	length = FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);
	std::cout << "Example 1 Output:" << std::endl;
	PrintPath(pOutBuffer2, length);
	std::cout << "#############" << std::endl;

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
	return 0;
}
