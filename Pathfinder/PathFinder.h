#pragma once
#include <unordered_map>

#include "SquareGrid.h"

/**
 * Takes ownership of the grid on creation
 */
class PathFinder
{
public:
    struct CandidateRecord
    {
        grid::GridLocation coordinate;
        float cost_so_far;
        float estimated_total_cost;

        bool operator<(const CandidateRecord& other) const noexcept;
    };

    struct VisitedRecord
    {
        grid::GridLocation previous;
        float cost_so_far = 0;
    };

    explicit PathFinder(const grid::SquareGrid&& grid_ref);
    using heur_fn = float(const grid::GridLocation&, const grid::GridLocation&);

    bool find_path(const grid::GridLocation& entry, const grid::GridLocation& goal, heur_fn heuristic_func,
                   std::list<grid::GridLocation>& results);

    using pathfinding_map = std::unordered_map<grid::GridLocation, VisitedRecord, grid::GridLocation::hash_grid_location>;
    //Public so we can print it out in runtime
    pathfinding_map visited;

    inline const grid::SquareGrid& get_grid() const noexcept { return _grid; }

private:
    grid::SquareGrid _grid;
};
