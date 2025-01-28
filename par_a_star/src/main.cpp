#include "astar.h"
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>

#define COLS 2000
#define ROWS 2000
#define DENSITY 5


int main() 
{
    std::cout << "A* start" << std::endl;

    std::vector<std::vector<uint8_t>> grid(COLS, std::vector<uint8_t>(ROWS));

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, DENSITY);

    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            //std::mt19937 generator (seed);

            //grid[i][j] = generator() % 2;
            grid[i][j] = (distribution(generator) != DENSITY) ? 1 : 0;


        }
    }

    for (int i = 0; i < COLS; i++)
    {
        grid[i][0] = 1;
        grid[i][ROWS - 1] = 1;
    }

    std::cout << "seeek and destroy !!" << std::endl;
    
    AStar astar(grid);

    astar.runSearch();

    astar.CLI();


    std::cout << "A* end" << std::endl;
    return 0;
}