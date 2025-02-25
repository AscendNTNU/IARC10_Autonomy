#include "../include/bt_drone/map_discovered_area.hpp"


std::vector<std::vector<bool>> make_discovered_map(std::vector<NED> positions)
{
    assert(positions.size() > 0 && "No positions logged");


    std::vector<std::vector<bool>> output(RES_X, std::vector<bool>(RES_Y, 0));

    // Scalar multiplication in 2d
    auto sm = [](const NED& lhs, const NED& rhs)  {
        return lhs.north * rhs.north + lhs.east * rhs.east;
    };

    // Calculates the length of a vector
    auto length = [](const NED&v) {
        return sqrt(v.north * v.north + v.east * v.east);
    };

    NED vec, projection, comp_vec;

    for (size_t i = 0; i < positions.size() - 1; i++)
    {
        vec = positions[i + 1] - positions[i];


        // For every point
        for (int x = 0; x < RES_X; x++)
        {
            for (int y = 0; y < RES_Y; y++)
            {
                // Vector from last position to checked position
                comp_vec = NED{x - positions[i].north, y - positions[i].east, 0};

                // Projecting the vector from last position to this point, onto the line from last point to next point. 
                projection = vec * (sm(comp_vec, vec)) / sm(vec, vec);

                // If outside the radius
                if (length(comp_vec - projection) >= EXLPORATION_RADIUS) {
                    // If far off, move a bit faster
                    y += std::max(0, (int)(length(comp_vec - projection) - EXLPORATION_RADIUS) - 5); 
                    continue;
                }

                if (projection.north <= std::max(0., vec.north) && projection.north >= std::min(0., vec.north) && projection.east <= std::max(0., vec.east) && projection.east >= std::min(0., vec.east))
                {
                    output[x][y] = true;
                } else if (length(positions[i] - NED{(double)x, (double)y, 0}) < EXLPORATION_RADIUS || length(positions[i + 1] - NED{(double)x, (double)y, 0}) < EXLPORATION_RADIUS) 
                {
                    // For rounded corners
                    output[x][y] = true;
                }
            }

        }
    }

    return output;
}


/*

// Testing script
int main()
{   
    std::vector<NED>input{NED{1, 20, 3}, NED{75, 75, 3}, NED{75, 1, 1}, NED{150, 150, 2}, NED{0, 200, 0}, NED{230, 170, 0}, NED{230, 5, 0}};

    auto out = make_discovered_map(input);
    for (int x= 0; x < RES_X; x++)
    {
        for (int y = 0; y < RES_Y; y++)
        {
            std::cout << (out[x][y] ? "\033[3;102;30m#" : "\033[3;101;30m.");
        }
        std::cout << "\033[0m\n";
    }

}

*/