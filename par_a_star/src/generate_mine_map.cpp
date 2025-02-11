#include "generate_mine_map.h"
#include "constants.h"

double normalCDF2D(double x, double y, double std)
{
    return  (std::erf(x / std / sqrt(2)) - std::erf((x + 1) / std / sqrt(2))) *
            (std::erf(y / std / sqrt(2)) - std::erf((y + 1) / std / sqrt(2))) / 4;
}

long double normalCDF2D(long double x, long double y, long double std)
{
    return  (std::erfl(x / std / sqrtl(2)) - std::erfl((x + 1) / std / sqrtl(2))) *
            (std::erfl(y / std / sqrtl(2)) - std::erfl((y + 1) / std / sqrtl(2))) / 4;
}


std::vector<std::vector<double>> generateMineMap(std::vector<Mine<double>> recorded_mines)
{ 
    // x is the short side, y is the long side
    std::vector<std::vector<double>> output(RES_X, std::vector<double>(RES_Y, 0));

    for (const Mine<double> &mine : recorded_mines)    
    {   
        for (int x = (int)(mine.x - GAUSSIAN_BLUR_LIMIT * mine.std); x <= (int)(mine.x + GAUSSIAN_BLUR_LIMIT * mine.std); x++)
        {
            if (x < 0) continue;
            if (x >= RES_X) break;

            for (int y = (int)(mine.y - GAUSSIAN_BLUR_LIMIT * mine.std); y <= (int)(mine.y + GAUSSIAN_BLUR_LIMIT * mine.std); y++)
            {
                if (y < 0) continue;
                if (y >= RES_Y) break;

                output[x][y] += normalCDF2D(x - mine.x, y - mine.y, mine.std);
            }
        }
    }
    return output;
}


/*
Generates a new boolean map with 1 being within radius of a location with higher mine probability than threshold
*/
std::vector<std::vector<int>> dilateMineMap(std::vector<std::vector<double>> mine_map, double threshold, double radius)
{
    // Checks if a new point is with a circle of radius 
    auto is_within_distance = [](int dx, int dy, double radius) -> bool {return (double)(dx * dx + dy * dy) <= radius * radius;};    
    
    int max_x = mine_map.size(), max_y = mine_map[0].size();
    std::vector<std::vector<int>> dilated_map(max_x, std::vector<int>(max_y, 1));

    for (int x = 0; x < max_x; x++)
    {
        for (int y = 0; y < max_y ; y++)
        {
            if (mine_map[x][y] < threshold) continue;

            for (int dx = -radius; dx <= radius; dx++)
            {
                if (x + dx < 0) continue;
                if (x + dx >= max_x) break;


                for (int dy = -radius; dy <= radius; dy++)
                {
                    if (y + dy < 0) continue;
                    if (y + dy >= max_y) break;
                    if (!is_within_distance(dx, dy, radius)) continue;

                    dilated_map[x + dx][y + dy] = 0;
                }
            }
        }
    }

    return dilated_map;
}


// Interprets unexplored area as mines, and updates minemap
void merge_explored_map_into_mine_map(std::vector<std::vector<bool>> &mine_map, const std::vector<std::vector<bool>> &explored_map)
{
    for (size_t i = 0; i < mine_map.size(); i++)
    {
        for (size_t j = 0; j < mine_map[0].size(); j++)
        {
            // if either mine or unexplored, then 1. Safe to walk through 0
            mine_map[i][j] = (!explored_map[i][j]) || mine_map[i][j];
        }
    }
}

// Scales the positions in the real world to the corresponding pixels in map
void realworld_to_map(std::vector<Mine<double>> &mines)
{
    for (auto&p : mines)
    {
        p.x *= SCALING_FACTOR;
        p.y *= SCALING_FACTOR;
        p.std *= SCALING_FACTOR;
    }
}

// Nå med std::array<double, 2>, men det må nok endres.
void positionLogToMap(std::vector<std::array<double, 2>> points)
{
    

}


// int main() {

//     std::vector<Mine<double>> mines{{12.2, 9.6, 1}, {7.9, 23.1, 0.5}, {9.5, 32, 1}, {3.2, 3.2, 0.1}};

//     std::vector<std::vector<double>> m = generateMineMap(mines);

//     for (int y = 0; y < RES_LONG_SIDE; y++)
//     {
//         for (int x = 0; x < RES_SHORT_SIDE; x++)
//         {
//             std::cout << std::fixed << std::setprecision(2) << (m[y][x] >= 0.005 ? "\033[1;41m" : "\033[1;43m") << m[y][x] << "  ";
//         }
//         std::cout << "\033[1;0m\n";
//     }

//     std::vector<std::vector<bool>> dilated = dilateMineMap(m, 0.1, 4.);

//     for (int y = 0; y < RES_LONG_SIDE; y++)
//     {
//         for (int x = 0; x < RES_SHORT_SIDE; x++)
//         {
//             std::cout << (dilated[y][x] ? "\033[1;41m" : "\033[1;42m") <<  dilated[y][x] << "     ";
//         }
//         std::cout << "\033[1;0m\n";
//     }

//     std::cout << __cplusplus << std::endl;
// }