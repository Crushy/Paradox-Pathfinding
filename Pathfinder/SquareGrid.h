#pragma once

#define TRAVERSABLE 1
#define IMPASSABLE  0
#define MOVE_COST 1

#include <SFML/Config.hpp>
#include <iostream>
#include <vector>

namespace grid
{
    typedef unsigned char GridValue;
    typedef sf::Int8 GridCoordType;

    /*
    A 2D grid location
    */
    struct GridLocation
    {
        GridCoordType x = 0, y = 0;

        struct hash_grid_location
        {
            size_t operator()(const GridLocation& location) const noexcept
            {
                return std::hash<int>()(location.x) ^ std::hash<int>()(location.y);
            }
        };

        constexpr GridLocation() noexcept
        {
            this->x = 0;
            this->y = 0;
        }

        constexpr GridLocation(const GridCoordType x, const GridCoordType y) noexcept
        {
            this->x = x;
            this->y = y;
        }

        constexpr  bool operator==(const GridLocation& other) const noexcept
        {
            return (this->x == other.x && this->y == other.y);
        }

        constexpr bool operator!=(const GridLocation& other) const noexcept
        {
            return (this->x != other.x || this->y != other.y);
        }

        friend std::ostream& operator<<(std::ostream& os, GridLocation const& ourselves)
        {
            return os << "GridLocation(" << ourselves.x << " , " << ourselves.y << ")";
        }
    };

    /*
    A square grid. Ideally should implement a Generic Grid interface.
    */
    class SquareGrid
    {
    public:
        //Constants
        static constexpr int max_neighbours = 4;

        static inline int coordinates_2d_to_array(const int x, const int y, const int width) noexcept
        {
            return width * y + x;
        }

        static inline GridLocation coordinates_array_to_2d(const int i, const int width) noexcept
        {
            return {static_cast<GridCoordType>(i % width), static_cast<GridCoordType>(i / width)};
        }

        //Constructors
        SquareGrid(const unsigned char* grid, const int width, const int height) noexcept;

        //Method declarations
        inline const GridValue& get_element(int x, int y) const noexcept;
        const GridValue& get_element(const GridLocation& loc) const noexcept;

        void get_neighbours(GridLocation coord, std::vector<GridLocation>& to_fill) const;

        //Getters
        inline int width() const noexcept
        {
            return _width;
        }

        inline int height() const noexcept
        {
            return _height;
        }

        inline void to_console() const
        {
            //std::cout << _height << std::endl;

            for (int i = 0; i < _height; i++)
            {
                for (int j = 0; j < _width; j++)
                {
                    std::cout << get_element(j, i) + 1;
                }

                std::cout << '\n';
            }
        }

    private:
        int _width = 0;
        int _height = 0;
        const GridValue* _grid; //Ideally this should be using array_view but GLSL is not allowed
    };
}
