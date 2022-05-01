#include <iostream>
#include <vector>
#include <climits>
#include <queue>

//This is some fairly old school code so we have to disable a bunch of suggestions to use more modern C++
#pragma warning( disable : 26485 26481 26446 26429)

inline int manhattan(int currentIndex, int destinationIndex, int gridWidth) noexcept
{
    return std::abs(currentIndex % gridWidth - destinationIndex % gridWidth) + std::abs(currentIndex / gridWidth - destinationIndex / gridWidth);
}

// Just your basic A* implementation
int FindPath(const int nStartX, const int nStartY,
    const int nTargetX, const int nTargetY,
    const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
    int* pOutBuffer, const int nOutBufferSize)
{ 
    
    const int startIndex = nStartX + nStartY * nMapWidth;
    const int targetIndex = nTargetX + nTargetY * nMapWidth;

    //Leave early if we are on top of the goal
    if (startIndex == targetIndex)
    {
        return 0;
    }

    const int maxIndex = nMapWidth * nMapHeight;

    //Stores candidates for the next node to explore
    //Contains the estimated cost to target for a given coordinate,
    //as well as the coordinate itself
    struct CandidateRecord {
        int index;
        int estimatedCost;

        //Used for the priority_queue, ensures the smallest estimates are at the top() of the queue
        bool operator< (const CandidateRecord& other) const noexcept
        {
            return estimatedCost > other.estimatedCost;
        }
    };

    std::priority_queue<CandidateRecord> open;
    std::vector<bool> closed(maxIndex);

    struct VisitRecord {
        int estimatedCost;
        int costSoFar;
        int weCameFrom;
    };
    std::vector<VisitRecord> visitRecords(maxIndex);

    for (int i = 0; i < maxIndex; i++)
    {
        visitRecords[i].costSoFar = INT_MAX;
        //Estimates to the destination be calculated here instead since they won't change,
        //Alternatively we could calculate them "on the spot" if they turn out to be too cpu-intensive
        visitRecords[i].estimatedCost = manhattan(i, startIndex, nMapWidth);
        closed[i] = false;
    }

    //Start the search from the goal so in the end we don't have to reverse the path
    int currentIndex = targetIndex;
    open.emplace(CandidateRecord{ currentIndex, manhattan(currentIndex,startIndex,nMapWidth) });

    while (currentIndex != startIndex)
    {
        //If there's no more candidates that means we have exhausted every possible path.
        if (open.empty())
            return -1;
        
        currentIndex = open.top().index;
        open.pop();
        //closed[currentIndex] = true;

        //Get all the valid neighbours
        std::vector<int> neighbours;
        if (currentIndex >= nMapWidth)
            neighbours.push_back(currentIndex - nMapWidth);
        if (currentIndex + nMapWidth < maxIndex)
            neighbours.push_back(currentIndex + nMapWidth);
        if (currentIndex % nMapWidth != 0)
            neighbours.push_back(currentIndex - 1);
        if (currentIndex % nMapWidth != nMapWidth - 1)
            neighbours.push_back(currentIndex + 1);

        const int costSoFar = visitRecords.at(currentIndex).costSoFar;

        for (const int neighbourIndex : neighbours)
        {
            if (pMap[neighbourIndex] == 1 /*&& !closed[neighbourIndex]*/)
            {
                auto& oldRecord = visitRecords[neighbourIndex];
                const int newCost = costSoFar + 1;

                //Update the node record if we found a better path 
                //Or initialize it since costSoFar is initialized as an impossibly high number
                if (newCost < oldRecord.costSoFar)
                {
                    oldRecord.costSoFar = newCost;
                    oldRecord.weCameFrom = currentIndex;
                    open.emplace(CandidateRecord{ neighbourIndex, oldRecord.costSoFar + oldRecord.estimatedCost });
                }
            }
        }
    }

    int aux = startIndex;
    int i;
    for (i = 0; aux!=targetIndex; i++) {
        if (i > nOutBufferSize)
            return -1;

        pOutBuffer[i] = visitRecords[aux].weCameFrom;
        aux = visitRecords[aux].weCameFrom;
    }
    return i;
}


void PrintPath(const int* pOutBuffer1, int length) {
	std::cout << "\tLength: " << length << std::endl;
	std::cout << "\tPath: ";
	//std::copy(std::begin(pOutBuffer1), std::end(pOutBuffer1), std::ostream_iterator<int>(std::cout, ", "));

	for (int i = 0; i < length; i++) {
		std::cout << pOutBuffer1[i] << ", ";
	}
	std::cout << std::endl;
}

int main()
{
	//Init Pathfinding
	
	for (int i = 0; i < 1; i++) {
		//Example 1
		const unsigned char pMap1[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
		int pOutBuffer1[12];
		std::cout << "Example 1 Output:" << std::endl;
		int length = FindPath(0, 0, 1, 2, pMap1, 4, 3, pOutBuffer1, 12);
		PrintPath(pOutBuffer1, length);
		//std::cout << "#############" << std::endl;


		//Example 2
		const unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
		int pOutBuffer2[7];
		std::cout << "Example 2 Output:" << std::endl;
		length = FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);
		PrintPath(pOutBuffer2, length);
		//std::cout << "#############" << std::endl;

		//Extra test case
		int pOutBuffer3[150];
        const unsigned char pMap3[] = {
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

        std::cout << "Example 3 Output:" << std::endl;
		length = FindPath(0, 9, 1, 3, pMap3, 20, 10, pOutBuffer3, (sizeof(pOutBuffer3) / sizeof(*pOutBuffer3)));
		PrintPath(pOutBuffer3, length);

	}
	return 0;
}

#pragma warning( default : 26485 26481 26446 26429)