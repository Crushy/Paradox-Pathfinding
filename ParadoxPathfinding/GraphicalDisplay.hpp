#pragma once
#include <SFML/Graphics.hpp>
#include "SquareGrid.hpp"
#include "Utils.hpp"
#include "FPS.hpp"

class DisplayGridSFML
{
public:
	DisplayGridSFML(sf::RenderWindow window);
	~DisplayGridSFML();
	void InitializeDisplay();
	void Loop();
	void update(const sf::RenderWindow & win, float delta);
protected:
	SquareGrid displayedGrid;
	sf::RenderWindow& windowHandle;

	float squareSize;

private:
	float gridMargin = 5;
	float padding;
	float gridSpace;
	sf::Vector2i cursorPosition;

	void ResizeWindow(sf::Vector2i newSize);

	FPS fpsCounter;

	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;

	sf::Clock sessionClock;
};

