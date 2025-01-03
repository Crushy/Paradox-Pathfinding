# ParadoxPathfinding

My attempt at solving the [Paradox Path-finding Challenge (dead link)](https://paradox.kattis.com/problems/paradoxpath). The Challenge required writing what amounted to plain old C, but I tried wrapping it in modern-ish C++.

Made in Visual Studio using MSVC 142 and C++14.

## Projects
### Submission
The First Project in the solution ( `Submission` ) is my actual submission. Due to necessity, it does not rely on any outside code and is it's entirety consists of a single (very messy) file.

### UIPathFinder
I wrote a simple UI in SMFL 2.5.1 to debug the paths it would find and check if there were any edge cases I missed - this is the second project, `UIPathFinder`.

I have included only the relevant libraries for Windows x86. Only runs in x86 until I can be arsed to change that.

Press 1 to set a start point and 2 to set the end point. Use the arrow keys to navigate.

# Problem Description
(Including typos, minimal formatting fixes)

## Path-finding

Problem ID: paradoxpath
Time limit: 5 seconds
Memory limit: 1024 MB

Difficulty
hard

Implement a path-finding algorithm in C++ that finds and returns a shortest path between two points in a 2-dimensional grid.

Note that this specific problem can only be solved using C++.
## API

Your algorithm should provide an implementation of the following function declaration.

    int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY, 
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);

The meaning of the parameters are as follows.

    nStartX and nStartY are the 00-based coordinates of the start position.

    nTargetX and nTargetY are the 00-based coordinates of the target position.

    pMap describes a grid of width nMapWidthnMapWidth and height nMapHeightnMapHeight. The grid is given in row-major order, each row is given in order of increasing xx-coordinate, and the rows are given in order of increasing yy-coordinate. Traversable locations of the grid are indicated by 1, and impassable locations are indicated by 0. Locations are considered to be adjacent horizontally and vertically but not diagonally.

    pOutBuffer is where you should store the positions visited in the found path, excluding the starting position but including the final position. Entries in pOutBuffer are indices into pMap. If there is more than one shortest path from Start to Target, any one of them will be accepted.

    nOutBufferSize is the maximum number of entries that can be written to pOutBuffer.

The function must return the length of the shortest path between Start and Target, or −1 if no such path exists.

If the shortest path is longer than `nOutBufferSize`, the calling function might either give up or choose to call FindPath again with a larger output buffer.
## Constraints

You may safely assume that:

    1≤nMapWidth,nMapHeight1≤nMapWidth,nMapHeight,

    0≤nStartX,nTargetX<nMapWidth0≤nStartX,nTargetX<nMapWidth,

    0≤nStartY,nTargetY<nMapHeight0≤nStartY,nTargetY<nMapHeight,

    Both Start and Target are empty locations,

    nOutBufferSize≥0nOutBufferSize≥0.

## Examples

    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[12];
    FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    For this input FindPath must return 33, and the first three positions of pOutBuffer must be populated with {1, 5, 9}.

    unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    int pOutBuffer[7];
    FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

    For this input FindPath must return −1.

## Additional considerations

Consider performance, memory usage and assume that your code may be called from a multi-threaded environment.
