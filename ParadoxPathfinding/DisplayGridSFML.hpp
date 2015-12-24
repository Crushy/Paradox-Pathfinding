#pragma once
#include <SFML/Graphics.hpp>
#include "SquareGrid.hpp"
#include "FPS.hpp"
#include "PathFinder.hpp"

class DisplayGridSFML
{
public:
	DisplayGridSFML(const Grid::SquareGrid& displayedGrid);
	~DisplayGridSFML();
	
	PathFinder& pathfinder;

	void Run();
protected:
	const Grid::SquareGrid& displayedGrid;
	

	sf::RenderWindow* window;
	void InitializeDisplay();
	float squareSize = 100;

private:
	float gridMargin = 0;
	float padding;
	float gridSpace;


	sf::Vector2i cursorPosition;

	//Shapes
	sf::RectangleShape gridSquare;
	sf::CircleShape cursorIndicator;

	Grid::GridLocation entry;
	Grid::GridLocation goal;

	void ResizeWindow(sf::Vector2u newSize);

	FPS fpsCounter;

	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;

	sf::Clock sessionClock;

	void RecalculatePath();
};

