#include "stdafx.h"

#include <SFML/Graphics.hpp>

#include "FPS.hpp"

#include <ostream>
#include <array>
#include <memory>

typedef unsigned char GridValue;

struct Vector2UInt {
	unsigned int x = 0;
	unsigned int y = 0;

	Vector2UInt() {
		this->x = 0;
		this->y = 0;
	}

	Vector2UInt(unsigned int x, unsigned int y) {
		this->x = x;
		this->y = y;
	}

	bool operator== (const Vector2UInt &other) const {
		return (this->x == other.x && this->y == other.y);
	}

	friend std::ostream &operator<<(std::ostream &os, Vector2UInt const &ourselves) {
		return os << "Vector2UInt(" << ourselves.x << " , " << ourselves.y << ")";
	}
};

struct GridItem {
	Vector2UInt coordinate;
	GridValue value = 1;

	GridItem()
	{
		this->coordinate = Vector2UInt();
		this->value = GridValue();
	}

	GridItem(Vector2UInt coordinate, GridValue val) {
		this->coordinate = coordinate;
		this->value = val;
	}

	friend std::ostream &operator<<(std::ostream &os, GridItem const &ourselves) {
		return os << "GridItem( Value:" << ourselves.value << " " << ourselves.coordinate << " )";
	}
	
};

class GridData {
	public :
		GridValue* grid; //Ideally this should be using array_view but I have no idea GLSL is allowed
		
		GridItem GetElement(int x, int y) {
			return GridItem(Vector2UInt(x,y), this->grid[Coordinates2DToArray(x, y, this->_width)]);
		}

		int Coordinates2DToArray(int x, int y, int width) {
			return width*y + x;
		}
		
		GridData(unsigned char* grid, int width, int height, Vector2UInt entry, Vector2UInt goal) {

			this->grid = grid;

			this->_width = width;
			this->_height = height;

			this->_entry = entry;
			this->_goal = goal;
			return;
		}

		void GetNeighbours(Vector2UInt coord, std::vector<GridItem>& toFill) {
			toFill.clear();

			//North
			if (coord.y > 0) {
				toFill.push_back(GetElement(coord.x, coord.y - 1));
				//toFill. = ;
			}
			//West
			if (coord.x > 0) {
				toFill.push_back(GetElement(coord.x - 1, coord.y));
				//toFill[index] = ;
			}
			//East
			if (coord.x < this->_width) {
				toFill.push_back(GetElement(coord.x + 1, coord.y));
				//toFill[index] = ;
			}
			//South
			if (coord.y < this->_height) {
				toFill.push_back(GetElement(coord.x, coord.y + 1));
				//toFill[index] = ;
			}
			/*
			for (std::vector<GridItem>::const_iterator j = toFill.begin(); j != toFill.end(); ++j)
			{
				std::cout << coord << (*j) << std::endl;
			}*/

		}

		const Vector2UInt entry() 
		{ 
			return _entry; 
		}

		const Vector2UInt goal()
		{
			return _goal;
		}

		const unsigned int width()
		{
			return _width;
		}

		const unsigned int height()
		{
			return _height;
		}

	private :
		unsigned int _width;
		unsigned int _height;
		Vector2UInt _entry;
		Vector2UInt _goal;

	
};

Vector2UInt CoordinatesArrayTo2D(int i, int width) {
	return Vector2UInt(i % width, i / width);
}


float lerp(float value, float start, float end)
{
	return start + (end - start) * value;
}



sf::Vector2f circlePos;

int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize) {

	return 0;
}


void update(const sf::RenderWindow& win, float delta) {
	//circlePos.x = win.getSize().x/2.f;
	//circlePos.y = lerp((sin(delta*2) / 2.f + .5f), 100, win.getSize().y - 100);
}

float gridMargin = 5;

Vector2UInt cursorPosition;

//Clamps from min (inclusive) to max (exclusive)
int clamp(int val, int min, int max) {
	int ret = std::min(val, max-1);
	ret = std::max(ret, min);
	return ret;
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(400, 400), "Pathfinding");

	sf::CircleShape bouncyCircle(100.f);
	bouncyCircle.setOrigin(100.f, 100.f);
	bouncyCircle.setFillColor(sf::Color::Green);
	

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

	GridData data = GridData(map,width,height,Vector2UInt(2,0),Vector2UInt(0,2));

	while (window.isOpen())
	{

		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed :
					window.close();
					break;
				case sf::Event::Resized :
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
				case sf::Event::KeyPressed :
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
						cursorPosition.x = clamp(cursorPosition.x + 1, 0, data.width() );
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
		
		
		bouncyCircle.setPosition(circlePos);
		//bouncyCircle.setPosition(window.getSize().x,0);


		int smallestDimension = window.getSize().x;// < window.getSize().y ? window.getSize().x: window.getSize().y;
		float padding = gridMargin;
		float gridSpace = smallestDimension - padding*2;
		float squareSize = ((gridSpace - gridMargin*(width-1)) / width);

		gridSquare.setSize(sf::Vector2f(gridSpace, gridSpace));
		gridSquare.setPosition(padding, padding);
		gridSquare.setFillColor(sf::Color::Black);
		window.draw(gridSquare);

		//float padding = (smallestDimension - (squareSize*_width + gridMargin * 4)) / 2;


		std::vector<GridItem> test = std::vector<GridItem>(4); //Start with size 4 since we only need 4 at most
		data.GetNeighbours(cursorPosition, test);

		for (int i = 0; i < width*height; i++)
		{
			Vector2UInt coord = CoordinatesArrayTo2D(i,width);

			gridSquare.setSize(sf::Vector2f(squareSize,squareSize));
			gridSquare.setPosition
				(
					padding + coord.x*(squareSize + gridMargin),
					padding +coord.y*(squareSize + gridMargin)
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
				default :
					gridSquare.setFillColor(sf::Color::Magenta);
					break;
			}
			
			if (coord == data.entry()) {
				gridSquare.setFillColor(sf::Color::Blue);
			}
			else if (coord == data.goal()) {
				gridSquare.setFillColor(sf::Color::Red);
			}

			for (std::vector<GridItem>::const_iterator j = test.begin(); j != test.end(); ++j)
			{
				std::cout << *j << std::endl;
				if ((j->coordinate) == coord) {
					gridSquare.setFillColor(sf::Color::Green);
					break;
				}
				else {
					continue;
				}
			}


			

			window.draw(gridSquare);
		}

		
		//window.draw(bouncyCircle);
		

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

