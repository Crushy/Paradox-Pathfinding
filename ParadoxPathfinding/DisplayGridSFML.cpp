#include "DisplayGridSFML.hpp"

DisplayGridSFML::DisplayGridSFML(const Grid::SquareGrid& grid, PathFinder& newpathfinder):
	displayedGrid(grid),
	pathfinder(newpathfinder)
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

	gridCircle.setFillColor(sf::Color::Magenta);

	return;
}

void DisplayGridSFML::RecalculatePath()
{
	
	//pathfinder.grid.ToConsole();
	pathfound = pathfinder.Pathfind(entry,goal,Utils::ManhattanDistance);
	//PrintPath(pathfound,pa)
	std::cout << "Length: " << pathfound->size() << std::endl;
	//std::cout << "Length: " << pathfound->size() << std::endl;
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
			window->draw(gridSquare);
		}

		if (pathfound != nullptr) {
			for each (auto var in (*pathfinder.visited))
			{
				gridSquare.setPosition(
					padding + var.second.coordinate.x*(squareSize + gridMargin),
					padding + var.second.coordinate.y*(squareSize + gridMargin)
					);
				gridSquare.setFillColor(sf::Color(128, 255, 128));
				window->draw(gridSquare);
			}
			
		}

		if (pathfound != nullptr) {
			for each (GridLocation var in *pathfound)
			{
				gridSquare.setPosition(
					padding + var.x*(squareSize + gridMargin),
					padding + var.y*(squareSize + gridMargin)
					);
				gridSquare.setFillColor(sf::Color::Green);
				window->draw(gridSquare);
			}

		}

		//Entry
		{
			gridCircle.setPosition(
				padding + entry.x*(squareSize + gridMargin),
				padding + entry.y*(squareSize + gridMargin)
				);
			gridCircle.setFillColor(sf::Color::Blue);
			window->draw(gridCircle);
		}
		//Goal
		{
			gridCircle.setPosition(
				padding + goal.x*(squareSize + gridMargin),
				padding + goal.y*(squareSize + gridMargin)
				);
			gridCircle.setFillColor(sf::Color::Red);
			window->draw(gridCircle);
		}

		//Cursor display
		float cursorSize = squareSize / 2;
		gridCircle.setRadius(cursorSize);
		gridCircle.setPosition(
			padding + cursorPosition.x*(squareSize + gridMargin),
			padding + cursorPosition.y*(squareSize + gridMargin)
			);
		gridCircle.setFillColor(sf::Color::Magenta);
		window->draw(gridCircle);

		//Draw fps counter
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
	float aspectRatio = (float)displayedGrid.width() / (float)displayedGrid.height();
	//std::cout << "Aspect ratio: "<< std::fixed << aspectRatio << std::endl;

	auto windowSize = window->getSize();
	int largestDimension, smallestDimension;
	sf::Vector2u desiredSize;
	if (newSize.x < newSize.y) //Resizing and width is larger than height
	{
		largestDimension = windowSize.x;
		smallestDimension = windowSize.y;
		desiredSize = sf::Vector2u(window->getSize().y * aspectRatio, window->getSize().y);
	}
	else //Height is larger than Width
	{
		largestDimension = windowSize.y;
		smallestDimension = windowSize.x;
		
		desiredSize = sf::Vector2u(window->getSize().x, window->getSize().x / aspectRatio);
	}
	
	//std::cout << "Size we want: " << desiredSize.x << "," << desiredSize.y << std::endl;

	window->setSize(desiredSize);
	
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

