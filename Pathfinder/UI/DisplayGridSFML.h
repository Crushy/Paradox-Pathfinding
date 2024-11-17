#pragma once
#pragma warning( disable : 26455 26432 26440 26429)
#include <SFML/Graphics.hpp> // Old school header, need to ignore a bunch of warnings
#pragma warning( default : 26455 26432 26440 26429)

#include <SFML/System/Time.hpp>
#include "FPS.hpp"
#include "../PathFinder.h"

namespace grid
{
    class SquareGrid;
}

class DisplayGridSFML
{
public:
    DisplayGridSFML(PathFinder&& new_pathfinder);
    void run();

protected:
    std::unique_ptr<sf::RenderWindow, std::default_delete<sf::RenderWindow>> _window;
    void initialize_display();
    float _square_size = 100;

private:
    void resize_window(sf::Vector2u new_size);
    void recalculate_path();
    void draw_shape(sf::Shape& shape, float x, float y, const sf::Color& color) const;

    PathFinder _pathfinder;
    float _grid_margin = 0;
    float _padding;
    float _grid_space;

    sf::Vector2i _cursor_position;

    //Shapes
    sf::RectangleShape _square_shape;
    sf::CircleShape _circle_shape;

    grid::GridLocation _entry;
    grid::GridLocation _goal;

    FPS _fps_counter;

    //Used to limit maximum frame rate
    sf::Clock _clock;
    sf::Time _elapsed = sf::Time::Zero;
    sf::Clock _sessionClock;

    std::list<grid::GridLocation> _pathfound;
};
