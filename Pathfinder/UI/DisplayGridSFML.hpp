#pragma once
#pragma warning( disable : 26455 26432 26440 26429)
#include <SFML/Graphics.hpp> // Old school header, need to ignore a bunch of warnings
#pragma warning( default : 26455 26432 26440 26429)

#include <SFML/System/Time.hpp>
#include "FPS.hpp"
#include "../PathFinder.hpp"

namespace Grid
{
	class SquareGrid;
}

class DisplayGridSFML
{
public:
	DisplayGridSFML(const Grid::SquareGrid& displayedGrid, PathFinder& newpathfinder);
	
	PathFinder& pathfinder;

	void Run();
protected:
	const Grid::SquareGrid& displayedGrid;

	std::unique_ptr<sf::RenderWindow, std::default_delete<sf::RenderWindow>> window;
	void InitializeDisplay();
	float squareSize = 100;

private:
	float gridMargin = 0;
	float padding;
	float gridSpace;

	sf::Vector2i cursorPosition;

	//Shapes
	sf::RectangleShape gridSquare;
	sf::CircleShape gridCircle;

	Grid::GridLocation entry;
	Grid::GridLocation goal;

	void ResizeWindow(sf::Vector2u newSize);

	FPS fpsCounter;

	//Used to limit maximum frame rate
	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;

	sf::Clock sessionClock;

	void RecalculatePath();

	std::list<GridLocation> pathfound;
};

