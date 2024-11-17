#include "DisplayGridSFML.h"

#include "../SquareGrid.h"
#include "../Utils.hpp"

DisplayGridSFML::DisplayGridSFML(PathFinder&& new_pathfinder):
    //_displayed_grid(displayed_grid),
    _pathfinder(std::move(new_pathfinder))
{
    initialize_display();
    return;
}

void DisplayGridSFML::initialize_display()
{
    _window = std::make_unique<sf::RenderWindow>();

    _window->create(sf::VideoMode(400, 400), "Pathfinding");

    //Window settings
    _window->setVerticalSyncEnabled(false);
    _window->setFramerateLimit(-1);

    resize_window(sf::Vector2u(400, 400));

    _circle_shape.setFillColor(sf::Color::Magenta);

    _fps_counter.Initialize();
    return;
}

void DisplayGridSFML::recalculate_path()
{
    if (_pathfinder.find_path(_entry, _goal, utils::manhattan_distance, _pathfound))
        std::cout << "Length: " << _pathfound.size() << '\n';
}


void DisplayGridSFML::run()
{
    auto& _displayed_grid = _pathfinder.get_grid();
    sf::Event event;
    while (_window->isOpen())
    {
        _clock.restart();

        while (_window->pollEvent(event))
        {
            // ReSharper disable once CppIncompleteSwitchStatement
            // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
            switch (event.type) // NOLINT(clang-diagnostic-switch-enum, clang-diagnostic-switch)
            {
            case sf::Event::Closed:
                _window->close();
                break;
            case sf::Event::Resized:
                resize_window(_window->getSize());
                break;
            case sf::Event::KeyPressed: //Move the cursor
                // ReSharper disable once CppIncompleteSwitchStatement
                // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
                switch (event.key.code) // NOLINT(clang-diagnostic-switch-enum, clang-diagnostic-switch)
                {
                case sf::Keyboard::W:
                case sf::Keyboard::Numpad8:
                case sf::Keyboard::Up:
                    _cursor_position.y = utils::clamp(_cursor_position.y - 1, 0, _displayed_grid.height());
                    break;
                case sf::Keyboard::S:
                case sf::Keyboard::Numpad2:
                case sf::Keyboard::Down:
                    _cursor_position.y = utils::clamp(_cursor_position.y + 1, 0, _displayed_grid.height());
                    break;
                case sf::Keyboard::A:
                case sf::Keyboard::Numpad4:
                case sf::Keyboard::Left:
                    _cursor_position.x = utils::clamp(_cursor_position.x - 1, 0, _displayed_grid.width());
                    break;
                case sf::Keyboard::D:
                case sf::Keyboard::Numpad6:
                case sf::Keyboard::Right:
                    _cursor_position.x = utils::clamp(_cursor_position.x + 1, 0, _displayed_grid.width());
                    break;
                case sf::Keyboard::Escape:
                    _window->close();
                    break;
                case sf::Keyboard::Num1:
                    this->_entry = grid::GridLocation(static_cast<grid::GridCoordType>(_cursor_position.x),
                                                      static_cast<grid::GridCoordType>(_cursor_position.y));
                    recalculate_path();
                    break;
                case sf::Keyboard::Num2:
                    this->_goal = grid::GridLocation(static_cast<grid::GridCoordType>(_cursor_position.x),
                                                     static_cast<grid::GridCoordType>(_cursor_position.y));
                    recalculate_path();
                    break;
                }
            }
        }

        _window->clear(sf::Color(0, 225, 225));

        //update(this->window, sessionClock.getElapsedTime().asSeconds());

        //float padding = (smallestDimension - (squareSize*_width + gridMargin * 4)) / 2;

        for (int i = 0; i < _displayed_grid.width() * _displayed_grid.height(); i++)
        {
            const grid::GridLocation coordLoc = grid::SquareGrid::coordinates_array_to_2d(i, _displayed_grid.width());

            _square_shape.setSize(sf::Vector2f(_square_size, _square_size));
            _square_shape.setPosition
            (
                _padding + (_square_size + _grid_margin) * static_cast<float>(coordLoc.x),
                _padding + (_square_size + _grid_margin) * static_cast<float>(coordLoc.y)
            );

            const grid::GridValue& curr_tile_val = _displayed_grid.get_element(coordLoc);
            switch (curr_tile_val)
            {
            case TRAVERSABLE:
                _square_shape.setFillColor(sf::Color::White);
                break;
            case IMPASSABLE:
                _square_shape.setFillColor(sf::Color(127, 127, 127));
                break;
            default:
                _square_shape.setFillColor(sf::Color::Magenta);
                break;
            }
            _window->draw(_square_shape);
        }

        // Display visited tiles
        if (!_pathfound.empty())
        {
            for (const auto& var : _pathfinder.visited)
            {
                draw_shape(_square_shape,
                           _padding + var.first.x * (_square_size + _grid_margin),
                           _padding + var.first.y * (_square_size + _grid_margin),
                           sf::Color(128, 255, 128)
                );
            }
        }

        // Display Path
        if (!_pathfound.empty())
        {
            for (const auto& var : _pathfound)
            {
                draw_shape(
                    _square_shape,
                    _padding + (_square_size + _grid_margin) * var.x,
                    _padding + (_square_size + _grid_margin) * var.y,
                    sf::Color::Green
                );
            }
        }

        //Draw Entry position
        {
            draw_shape(_circle_shape,
                       _padding + _entry.x * (_square_size + _grid_margin),
                       _padding + _entry.y * (_square_size + _grid_margin),
                       sf::Color::Blue
            );
        }
        //Draw Goal position
        {
            draw_shape(_circle_shape, _padding + _goal.x * (_square_size + _grid_margin),
                       _padding + _goal.y * (_square_size + _grid_margin),
                       sf::Color::Red);
        }

        //Draw "Cursor"
        const float cursorSize = _square_size / 2;
        _circle_shape.setRadius(cursorSize);
        draw_shape(
            _circle_shape,
            _padding + _cursor_position.x * (_square_size + _grid_margin),
            _padding + _cursor_position.y * (_square_size + _grid_margin),
            sf::Color::Magenta
        );

        //Draw fps counter
        _fps_counter.DrawFPSCount(_window.get());

        _window->display();

        _elapsed = _clock.getElapsedTime();
        const float sleepTime = 1.f / 120.f - _elapsed.asSeconds();
        if (sleepTime > 0.f)
        {
            sf::sleep(sf::seconds(sleepTime));
        }

        _fps_counter.Update();
    }
}

inline void DisplayGridSFML::draw_shape(sf::Shape& shape, const float x, const float y, const sf::Color& color) const
{
    shape.setPosition(
        x,
        y
    );
    shape.setFillColor(color);
    _window->draw(shape);
}

void DisplayGridSFML::resize_window(sf::Vector2u new_size)
{
    auto& _displayed_grid = _pathfinder.get_grid();

    const float aspectRatio = static_cast<float>(_displayed_grid.width()) / static_cast<float>(_displayed_grid.
        height());
    //std::cout << "Aspect ratio: "<< std::fixed << aspectRatio << std::endl;

    const auto windowSize = _window->getSize();
    int largestDimension, smallestDimension;
    sf::Vector2u desiredSize;
    if (new_size.x < new_size.y) //Width is larger than height
    {
        largestDimension = windowSize.x;
        smallestDimension = windowSize.y;
        //Disable warning about loss of precision
#pragma warning( disable : 26467 )
        desiredSize = sf::Vector2u(static_cast<unsigned int>((_window->getSize().y * aspectRatio)),
                                   _window->getSize().y);
#pragma warning( default : 26467 )
    }
    else //Height is larger than Width
    {
        largestDimension = windowSize.y;
        smallestDimension = windowSize.x;
        //Disable warning about loss of precision
#pragma warning( disable : 26467 )
        desiredSize = sf::Vector2u(_window->getSize().x, static_cast<unsigned int>(_window->getSize().x / aspectRatio));
#pragma warning( default : 26467 )
    }

    //std::cout << "Size we want: " << desiredSize.x << "," << desiredSize.y << std::endl;

    _window->setSize(desiredSize);

    this->_padding = _grid_margin;
    this->_grid_space = smallestDimension - _padding * 2;
    this->_square_size = (_grid_space - _grid_margin * (_displayed_grid.width() - 1)) / _displayed_grid.width();


    _window->setView
    (
        sf::View
        (
            sf::FloatRect
            (
                0.f, 0.f,
                static_cast<float>(_window->getSize().x),
                static_cast<float>(_window->getSize().y)
            )
        )
    );
}
