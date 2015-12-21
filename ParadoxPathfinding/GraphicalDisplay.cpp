#include "GraphicalDisplay.hpp"

DisplayGridSFML::DisplayGridSFML(sf::RenderWindow window) :
	windowHandle(window)
{
	return;
}


DisplayGridSFML::~DisplayGridSFML()
{
}

void DisplayGridSFML::InitializeDisplay()
{
	//sf::Window win = sf::Window();
	windowHandle.setSize(sf::Vector2u(400,400));
	windowHandle.setTitle("Pathfinding");

	sf::CircleShape cursorIndicator(100.f);
	cursorIndicator.setFillColor(sf::Color::Green);

	//Window settings
	//window.setVerticalSyncEnabled(false);
	//window.setFramerateLimit(60);


	sf::RectangleShape gridSquare(sf::Vector2f(10.f, 10.f));

	while (windowHandle.isOpen())
	{

		clock.restart();

		sf::Event event;
		while (windowHandle.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				windowHandle.close();
				break;
			case sf::Event::Resized:
				windowHandle.setView
					(
						sf::View
						(
							sf::FloatRect
							(
								0.f, 0.f,
								static_cast<float>(windowHandle.getSize().x),
								static_cast<float>(windowHandle.getSize().y)
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
					windowHandle.close();
					break;
				}

			default:
				break;
			}

		}

		this->windowHandle.clear(sf::Color(0, 225, 225));

		update(this->windowHandle, sessionClock.getElapsedTime().asSeconds());


		
		gridSquare.setSize(sf::Vector2f(gridSpace, gridSpace));
		gridSquare.setPosition(padding, padding);
		gridSquare.setFillColor(sf::Color::Black);
		this->windowHandle.draw(gridSquare);

		//float padding = (smallestDimension - (squareSize*_width + gridMargin * 4)) / 2;




		for (int i = 0; i < displayedGrid.width()*displayedGrid.height(); i++)
		{
			Grid::GridLocation coordLoc = this->displayedGrid.CoordinatesArrayTo2D(i, displayedGrid.width());

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
			/*
			if (coord == data.entry()) {
			gridSquare.setFillColor(sf::Color::Blue);
			}
			else if (coord == data.goal()) {
			gridSquare.setFillColor(sf::Color::Red);
			}*/
			windowHandle.draw(gridSquare);
		}

		//Cursor display
		float cursorSize = squareSize / 2;
		cursorIndicator.setRadius(cursorSize);
		cursorIndicator.setPosition(
			padding + cursorPosition.x*(squareSize + gridMargin),
			padding + cursorPosition.y*(squareSize + gridMargin)
			);

		windowHandle.draw(cursorIndicator);


		fpsCounter.DrawFPSCount(this->windowHandle);
		windowHandle.display();



		elapsed = clock.getElapsedTime();
		float sleepTime = 1.f / 120.f - elapsed.asSeconds();
		if (sleepTime > 0.f)
		{
			sf::sleep(sf::seconds(sleepTime));
		}

		fpsCounter.update();
	}

	return;
}

void DisplayGridSFML::Loop()
{
}

void DisplayGridSFML::update(const sf::RenderWindow& win, float delta) {

}

void DisplayGridSFML::ResizeWindow(sf::Vector2i newSize)
{
	int smallestDimension = windowHandle.getSize().x;// < window.getSize().y ? window.getSize().x: window.getSize().y;
	this->padding = gridMargin;
	this->gridSpace = smallestDimension - padding * 2;
	this->squareSize = ((gridSpace - gridMargin*(displayedGrid.width() - 1)) / displayedGrid.width());

}

