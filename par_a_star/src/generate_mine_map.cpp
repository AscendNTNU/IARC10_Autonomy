#include<vector>
#include<cmath>
#include<iostream>
#include<iomanip>

template<typename T>
struct Mine {
    T x,        // mean_x 
    y,          // mean_y
    std;        // standard deviation

    Mine(T xpos, T ypos, T standard_deviation) {
        x = xpos, y = ypos, std = standard_deviation;
    }
} ;

// Constants
constexpr int 
RES_SHORT_SIDE = 20, // Resolution
RES_LONG_SIDE = 40;

double TwoDNormalCDF(double x, double y, double std)
{
    return  (std::erf(x / std / sqrt(2)) - std::erf((x + 1) / std / sqrt(2))) *
            (std::erf(y / std / sqrt(2)) - std::erf((y + 1) / std / sqrt(2))) / 4;
}

/*
Input: points corresponding to the observed mine locations. Should be in the coordinate system of the minefield
Output: heatmap of the mines
*/
template<typename T>
std::vector<std::vector<T>> generate_mine_map(std::vector<Mine<T>> recorded_mines)
{ 
    // x is the short side, y is the long side
    std::vector<std::vector<T>> output(RES_LONG_SIDE, std::vector<T>(RES_SHORT_SIDE, 0));

    constexpr double GAUSSIAN_BLUR_LIMIT = 4;

    for (const Mine<T> &mine : recorded_mines)    
    {   
        for (int x = (int)(mine.x - GAUSSIAN_BLUR_LIMIT * mine.std); x <= (int)(mine.x + GAUSSIAN_BLUR_LIMIT * mine.std); x++)
        {
            if (x < 0) continue;
            if (x >= RES_SHORT_SIDE) break;

            for (int y = (int)(mine.y - GAUSSIAN_BLUR_LIMIT * mine.std); y <= (int)(mine.y + GAUSSIAN_BLUR_LIMIT * mine.std); y++)
            {
                if (y < 0) continue;
                if (y >= RES_LONG_SIDE) break;

                output[y][x] += TwoDNormalCDF(x - mine.x, y - mine.y, mine.std);
            }
        }
    }
    return output;
}


/*
Generates a new boolean map with 1 being within radius of a location with higher mine probability than threshold
*/
template <typename T>
std::vector<std::vector<bool>> dilate_mine_map(std::vector<std::vector<T>> mine_map, T threshold, T radius)
{
    // Checks if a new point is with a circle of radius 
    auto is_within_distance = [](int dx, int dy, T radius) -> bool {return (T)(dx * dx + dy * dy) <= radius * radius;};    
    
    int max_y = mine_map.size(), max_x = mine_map[0].size();
    std::vector<std::vector<bool>> dilated_map(max_y, std::vector<bool>(max_x));

    for (int x = 0; x < max_x; x++)
    {
        for (int y = 0; y < max_y ; y++)
        {
            if (mine_map[y][x] < threshold) continue;

            for (int dx = -radius; dx <= radius; dx++)
            {
                if (x + dx < 0) continue;
                if (x + dx >= max_x) break;
                for (int dy = -radius; dy <= radius; dy++)
                {
                    if (y + dy < 0) continue;
                    if (y + dy >= max_y) break;
                    if (!is_within_distance(dx, dy, radius)) continue;

                    dilated_map[y + dy][x + dx] = true;
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



int main() {

    std::vector<Mine<double>> mines{{12.2, 9.6, 1}, {7.9, 23.1, 0.5}, {9.5, 32, 1}, {3.2, 3.2, 0.1}};

    std::vector<std::vector<double>> m = generate_mine_map(mines);

    for (int y = 0; y < RES_LONG_SIDE; y++)
    {
        for (int x = 0; x < RES_SHORT_SIDE; x++)
        {
            std::cout << std::fixed << std::setprecision(2) << (m[y][x] >= 0.005 ? "\033[1;41m" : "\033[1;43m") << m[y][x] << "  ";
        }
        std::cout << "\033[1;0m\n";
    }

    std::vector<std::vector<bool>> dilated = dilate_mine_map(m, 0.1, 4.);

    for (int y = 0; y < RES_LONG_SIDE; y++)
    {
        for (int x = 0; x < RES_SHORT_SIDE; x++)
        {
            std::cout << (dilated[y][x] ? "\033[1;41m" : "\033[1;42m") <<  dilated[y][x] << "     ";
        }
        std::cout << "\033[1;0m\n";
    }
}