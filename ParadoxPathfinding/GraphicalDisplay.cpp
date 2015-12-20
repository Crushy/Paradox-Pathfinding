#include "stdafx.h"
//#include "GraphicalDisplay.h"
//#include <SFML/Graphics.hpp>
//#include "FPS.hpp"
//#include "./ParadoxPathfinding.cpp"
/*
GraphicalDisplay::GraphicalDisplay()
{
}


GraphicalDisplay::~GraphicalDisplay()
{
}


void update(const sf::RenderWindow& win, float delta) {

}

float gridMargin = 5;

Vector2UInt cursorPosition;


int startDisplay()
{

	sf::RenderWindow window(sf::VideoMode(400, 400), "Pathfinding");

	sf::CircleShape cursorIndicator(100.f);
	cursorIndicator.setFillColor(sf::Color::Green);


	//Window settings
	//window.setVerticalSyncEnabled(false);
	//window.setFramerateLimit(60);


	FPS fpsCounter;


	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;

	sf::Clock sessionClock;


	sf::RectangleShape gridSquare(sf::Vector2f(10.f, 10.f));

	//Init Pathfinding

	unsigned char map[] = {
		1, 1, 1, 1,
		0, 1, 0, 1,
		0, 1, 1, 1
	};

	int width = 4;
	int height = 3;

	GridData data = GridData(map, width, height, Vector2UInt(2, 0), Vector2UInt(0, 2));

	while (window.isOpen())
	{

		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView
					(
						sf::View
						(
							sf::FloatRect
							(
								0.f, 0.f,
								static_cast<float>(window.getSize().x),
								static_cast<float>(window.getSize().y)
								)
							)
						);

				break;

			case sf::Event::KeyPressed: //Move the cursor
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Numpad8:
				case sf::Keyboard::Up:
					cursorPosition.y = clamp(cursorPosition.y - 1, 0, data.height());
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Numpad2:
				case sf::Keyboard::Down:
					cursorPosition.y = clamp(cursorPosition.y + 1, 0, data.height());
					break;
				case sf::Keyboard::A:
				case sf::Keyboard::Numpad4:
				case sf::Keyboard::Left:
					cursorPosition.x = clamp(cursorPosition.x - 1, 0, data.width());
					break;
				case sf::Keyboard::D:
				case sf::Keyboard::Numpad6:
				case sf::Keyboard::Right:
					cursorPosition.x = clamp(cursorPosition.x + 1, 0, data.width());
					break;
				case sf::Keyboard::Escape:
					window.close();
					break;
				}

			default:
				break;
			}

		}

		window.clear(sf::Color(0, 225, 225));

		update(window, sessionClock.getElapsedTime().asSeconds());


		int smallestDimension = window.getSize().x;// < window.getSize().y ? window.getSize().x: window.getSize().y;
		float padding = gridMargin;
		float gridSpace = smallestDimension - padding * 2;
		float squareSize = ((gridSpace - gridMargin*(width - 1)) / width);

		gridSquare.setSize(sf::Vector2f(gridSpace, gridSpace));
		gridSquare.setPosition(padding, padding);
		gridSquare.setFillColor(sf::Color::Black);
		window.draw(gridSquare);

		//float padding = (smallestDimension - (squareSize*_width + gridMargin * 4)) / 2;




		for (int i = 0; i < width*height; i++)
		{
			Vector2UInt coord = CoordinatesArrayTo2D(i, width);

			gridSquare.setSize(sf::Vector2f(squareSize, squareSize));
			gridSquare.setPosition
				(
					padding + coord.x*(squareSize + gridMargin),
					padding + coord.y*(squareSize + gridMargin)
					);

			GridValue currTileVal = data.grid[i];
			switch (currTileVal)
			{
			case 1:
				gridSquare.setFillColor(sf::Color::White);
				break;
			case 0:
				gridSquare.setFillColor(sf::Color(127, 127, 127));
				break;
			default:
				gridSquare.setFillColor(sf::Color::Magenta);
				break;
			}

			if (coord == data.entry()) {
				gridSquare.setFillColor(sf::Color::Blue);
			}
			else if (coord == data.goal()) {
				gridSquare.setFillColor(sf::Color::Red);
			}
			window.draw(gridSquare);
		}

		//Cursor display
		//std::vector<GridItem> test = std::vector<GridItem>(4); //Start with size 4 since we only need 4 at most
		//data.GetNeighbours(cursorPosition, test);
		float cursorSize = squareSize / 2;
		cursorIndicator.setRadius(cursorSize);
		cursorIndicator.setPosition(
			padding + cursorPosition.x*(squareSize + gridMargin),
			padding + cursorPosition.y*(squareSize + gridMargin)
			);

		window.draw(cursorIndicator);


		fpsCounter.DrawFPSCount(window);
		window.display();



		elapsed = clock.getElapsedTime();
		float sleepTime = 1.f / 120.f - elapsed.asSeconds();
		if (sleepTime > 0.f)
		{
			sf::sleep(sf::seconds(sleepTime));
		}

		fpsCounter.update();
	}

	return 0;
}
*/