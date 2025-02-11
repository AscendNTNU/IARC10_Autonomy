#include "astar.h"
#include "generate_mine_map.h"
#include "constants.h"

#include<random>
#include<fstream>
#include<cassert>



std::vector<Mine<double>> generate_random_mines(int num)
{
    std::random_device sd;

    std::mt19937 g(sd());

    std::uniform_real_distribution<double> short_side_distribution(0, AREA_X),
    long_side_distribution(0, AREA_Y), uncertanty_distribution(0.05, 0.1);


    std::vector<Mine<double>> output;

    for (int i = 0; i < num; i++)
    {
        output.emplace_back(Mine(short_side_distribution(g), long_side_distribution(g), uncertanty_distribution(g)));
    }

    return output;
}



void print_mine_map(std::vector<std::vector<double>> m)
{
    assert(m.size() == RES_X);
    assert(m[0].size() == RES_Y);
    std::ofstream output("minemap.txt");
    for (int y = 0; y < RES_Y; y++)
    {
        for (int x = 0; x < RES_X; x++)
        {
            output << std::fixed << std::setprecision(2) << m[x][y] << " ";
        }
        output << "\n";
    }
    output.close();
}

void print_bit_map(std::vector<std::vector<int>> dilated)
{
    std::ofstream output("bitmap.txt");
    assert(dilated.size() == RES_X);
    for (int y = 0; y < RES_Y; y++)
    {
        assert(dilated[0].size() == RES_Y);
        for (int x = 0; x < RES_X; x++)
        {
            output << dilated[x][y] << " ";
        }
        output << "\n";
    }
    output.close();
}



int main()
{
    std::vector<Mine<double>> mines = generate_random_mines(MINES);


    realworld_to_map(mines);

    std::vector<std::vector<double>> mine_map = generateMineMap(mines);
    std::vector<std::vector<int>> bit_map = dilateMineMap(mine_map, THRESHOLD, RADIUS * SCALING_FACTOR);

    std::cout << "Map size: " << mine_map.size() << " " << mine_map[0].size() << "\n";  
    print_mine_map(mine_map);
    print_bit_map(bit_map);

    AStar astar;
    astar.setGrid(bit_map);

    int h = astar.runSearch();
    

    astar.CLI2File("output.txt");

    std::cout << result << "\n";
}