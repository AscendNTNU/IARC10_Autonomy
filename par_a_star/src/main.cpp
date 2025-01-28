#include "astar.h"
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>

#define COLS 100
#define ROWS 100
#define DENSITY 5


int main() 
{
    std::cout << "A* start" << std::endl;

    std::vector<std::vector<int>> grid(COLS, std::vector<int>(ROWS));

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, DENSITY);

    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            grid[i][j] = (distribution(generator) != DENSITY) ? 1 : 0;
        }
    }

    for (int i = 0; i < COLS; i++)
    {
        grid[i][0] = 1;
        grid[i][ROWS - 1] = 1;

        grid[i][10] = 0;
        grid[COLS - 1][10] = 1;

        grid[i][5] = 0;
        grid[0][5] = 1;
    }

    std::cout << "seeek and destroy !!" << std::endl;
    
    AStar astar(grid);

    int h = astar.runSearch();
    

    astar.CLI();

    std::cout << "gikk det her a? " << h << std::endl;



    std::cout << "A* end" << std::endl;
    return 0;
}