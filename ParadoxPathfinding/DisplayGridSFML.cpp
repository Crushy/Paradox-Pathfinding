#include "DisplayGridSFML.hpp"

DisplayGridSFML::DisplayGridSFML(const Grid::SquareGrid& grid):
	displayedGrid(grid),
	pathfinder(PathFinder(grid))
{
	InitializeDisplay();
	return;
}


DisplayGridSFML::~DisplayGridSFML()
{
}

void DisplayGridSFML::InitializeDisplay()
{
	window = new sf::RenderWindow();
	window->create(sf::VideoMode(400, 400), "Pathfinding");

	//Window settings
	//window->setVerticalSyncEnabled(false);
	//window->setFramerateLimit(60);

	ResizeWindow(sf::Vector2u(400, 400));

	cursorIndicator.setFillColor(sf::Color::Magenta);

	return;
}

void DisplayGridSFML::RecalculatePath()
{
	
	pathfinder.grid.ToConsole();
	//pathfinder.Pathfind(entry,goal,Utils::ManhattanDistance);
	
}

void DisplayGridSFML::Run()
{
	sf::Event event;
	while (window->isOpen())
	{
		//pathfinder.grid.ToConsole();
		/**/
		clock.restart();
		
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::Resized:
				ResizeWindow(window->getSize());
				break;
			case sf::Event::KeyPressed: //Move the cursor
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Numpad8:
				case sf::Keyboard::Up:
					cursorPosition.y = Utils::clamp(cursorPosition.y - 1, 0, displayedGrid.height());
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Numpad2:
				case sf::Keyboard::Down:
					cursorPosition.y = Utils::clamp(cursorPosition.y + 1, 0, displayedGrid.height());
					break;
				case sf::Keyboard::A:
				case sf::Keyboard::Numpad4:
				case sf::Keyboard::Left:
					cursorPosition.x = Utils::clamp(cursorPosition.x - 1, 0, displayedGrid.width());
					break;
				case sf::Keyboard::D:
				case sf::Keyboard::Numpad6:
				case sf::Keyboard::Right:
					cursorPosition.x = Utils::clamp(cursorPosition.x + 1, 0, displayedGrid.width());
					break;
				case sf::Keyboard::Escape:
					window->close();
					break;
				case sf::Keyboard::Num1:
					this->entry = Grid::GridLocation(cursorPosition.x, cursorPosition.y);
					RecalculatePath();
					break;
				case sf::Keyboard::Num2:
					this->goal = Grid::GridLocation(cursorPosition.x, cursorPosition.y);
					RecalculatePath();
					break;
				}
			default:
				break;
			}

		}
		
		window->clear(sf::Color(0, 225, 225));
		
		//update(this->window, sessionClock.getElapsedTime().asSeconds());

		//float padding = (smallestDimension - (squareSize*_width + gridMargin * 4)) / 2;

		for (int i = 0; i < displayedGrid.width()*displayedGrid.height(); i++)
		{
			Grid::GridLocation coordLoc = displayedGrid.CoordinatesArrayTo2D(i, displayedGrid.width());

			gridSquare.setSize(sf::Vector2f(squareSize, squareSize));
			gridSquare.setPosition
				(
					padding + coordLoc.x*(squareSize + gridMargin),
					padding + coordLoc.y*(squareSize + gridMargin)
					);

			GridValue currTileVal = displayedGrid.GetElement(coordLoc);
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
			
			if (coordLoc == entry) 
			{
				gridSquare.setFillColor(sf::Color::Blue);
			}
			else if (coordLoc == goal)
			{
				gridSquare.setFillColor(sf::Color::Red);
			}
			window->draw(gridSquare);
		}

		//Cursor display
		float cursorSize = squareSize / 2;
		cursorIndicator.setRadius(cursorSize);
		cursorIndicator.setPosition(
			padding + cursorPosition.x*(squareSize + gridMargin),
			padding + cursorPosition.y*(squareSize + gridMargin)
		);

		window->draw(cursorIndicator);


		fpsCounter.DrawFPSCount(window);
		window->display();



		elapsed = clock.getElapsedTime();
		float sleepTime = 1.f / 120.f - elapsed.asSeconds();
		if (sleepTime > 0.f)
		{
			sf::sleep(sf::seconds(sleepTime));
		}

		fpsCounter.update();
	}
}

void DisplayGridSFML::ResizeWindow(sf::Vector2u newSize)
{
	int smallestDimension = window->getSize().x < window->getSize().y ? window->getSize().x: window->getSize().y;
	int largestDimension = window->getSize().x < window->getSize().y ? window->getSize().y : window->getSize().x;
	window->setSize(sf::Vector2u(largestDimension, largestDimension));
	
	this->padding = gridMargin;
	this->gridSpace = smallestDimension - padding * 2;
	this->squareSize = ((gridSpace - gridMargin*(displayedGrid.width() - 1)) / displayedGrid.width());


	window->setView
		(
			sf::View
			(
				sf::FloatRect
				(
					0.f, 0.f,
					static_cast<float>(window->getSize().x),
					static_cast<float>(window->getSize().y)
					)
				)
			);
}

