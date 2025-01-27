#include"dumb_lawnmower.h"
/*////////////////////////////////////////////////////////////////////////////////////////////////
Author: Adrian
Programmet finner 

*/////////////////////////////////////////////////////////////////////////////////////////////////


std::vector<NED> generate_path(NED starting_position, NED end_vector, NED path_vector, int resolution)
{
    std::vector<NED> output{starting_position};

    NED last = starting_position;
    for (int i = 1; i <= resolution; i++)
    {
        last += path_vector / (double)resolution;
        output.emplace_back(last);
    }

    last += end_vector;
    output.emplace_back(last);

    for (int i = 1; i <= resolution; i++)
    {
        last += path_vector / ((double)-resolution);
        output.emplace_back(last);
    }

    return output;

}

int main()
{
    NED 
    start_position{0, 0, -6},
    end_vector{4, 0, 0},
    path_vector{0, 90, 0};

    std::vector<NED> path = generate_path(start_position, end_vector, path_vector, 20);

    for (auto &p : path)
    {
        std::cout << p << "\n";
    }

}