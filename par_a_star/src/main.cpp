#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <queue>
#include <chrono>
#include <random>

#define COL 20
#define ROW 20
#define __PRINT_ENABLED__

typedef std::pair<int, int> Pair;

struct Node 
{
    //Current placement
    Pair coordinates;

    //Parent node coordinates
    Pair parent;

    //total cost, cost from start, cost to goal
    int f, g, h;

    bool beenVisited;

    bool isUnblocked;

    bool operator<(const Node &obj) const
    {
        return f > obj.f;
    }

};


//Determines if given point is at the destination
bool isDestination(Pair point)
{
    //for (int i = 0; i < destinationPoints.size(); i++) 
    //{
        //if (point.first == destinationPoints[i].first && point.second == destinationPoints[i].second)
        //{
            //return true;
        //}
    //}
    //return false;


    return point.first == (ROW - 1);
}

//Determines if a point on the grid is unblocked or not. 1 is unblocked, 0 is blocked
bool isUnblocked(std::vector<std::vector<uint8_t>> &grid, Pair point) 
{
    return grid[point.first][point.second] == 1;
}


//Determines lowest H value by computing distance from the last row
int determineHeuristic(Pair point) 
{
    return point.first - ROW + 1;
}

//Find range of indices around an index in an array. If it is an edge, return range [edge, index + 1] or [index - 1, edge]
Pair findRange(int arrayLength, int srcIndex)
{
    Pair range;

    if (srcIndex < 0 || srcIndex > arrayLength + 1)
    {
        return std::pair(0, 0);
    }

    //If index is at 0, return <index, index + 1>
    //if index is at arraylength
    srcIndex == 0 ? range.first = 0 : range.first = srcIndex - 1;
    srcIndex == arrayLength - 1 ? range.second = arrayLength - 1 : range.second = srcIndex + 1;

    return range;
}

//Denne tror jeg du skjønner
bool isItemInList(std::vector<Pair> &list, Pair item)
{
    for (Pair listItem : list)
    {
        if (listItem.first == item.first && listItem.second == item.second)
        {
            return true;
        }
    }
    return false;
}

std::vector<Pair> createRoute(std::vector<std::vector<Node>> &nodes, Node traceBackNode)
{
    std::vector<Pair> route;

    Node currentNode = traceBackNode;

    do
    {
        route.push_back(currentNode.coordinates);
        currentNode = nodes[currentNode.parent.first][currentNode.parent.second];
    }
    while (currentNode.coordinates != currentNode.parent);

    return route;
}


std::vector<Pair> findRoute(std::vector<std::vector<uint8_t>> &grid, std::vector<Pair> &srcPoints)
{
    std::vector<std::vector<Node>> nodes(ROW, std::vector<Node>(COL));
    
    // Alle noder blir foreldreløse og har max verdi
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            Pair coordinates = std::pair(i, j);

            nodes[i][j].f = INT16_MAX;
            nodes[i][j].g = INT16_MAX;
            nodes[i][j].h = INT16_MAX;
            nodes[i][j].parent = std::pair(-1, -1);
            nodes[i][j].coordinates = coordinates;
            nodes[i][j].beenVisited = false;
            nodes[i][j].isUnblocked = isUnblocked(grid, coordinates);
            

        }
    }

    //Initialize nodes to srcPoints
    std::priority_queue<Node> priorityQueue;
    //std::vector<Pair> visitedNodeCoordinates;

    for (Pair point : srcPoints)
    {
        int h = determineHeuristic(point);

        nodes[point.first][point.second].g = 0;
        nodes[point.first][point.second].h = h;
        nodes[point.first][point.second].f = h;
        nodes[point.first][point.second].parent = point;
        nodes[point.first][point.second].beenVisited = true;

        //openList.push_back(nodes[point.first][point.second]);
        priorityQueue.push(nodes[point.first][point.second]);
        //visitedNodeCoordinates.push_back(nodes[point.first][point.second].coordinates);
    }

    //Start searcch!!!!!
    std::vector<Pair> route;

    while (!priorityQueue.empty())
    {
        //Choose node with lowest f-value from the priorityQueue
        Node currentNode = priorityQueue.top();


        //CurrentPoint is at destination? return route
        if (isDestination(currentNode.coordinates)) 
        {
            route = createRoute(nodes, currentNode);
            priorityQueue = std::priority_queue<Node>();
        }
        else
        {
            //Find availible parents to node
            Pair rowRange = findRange(ROW, currentNode.coordinates.first);
            Pair colRange = findRange(COL, currentNode.coordinates.second);

            priorityQueue.pop();

            //For each neighbor to currentNode
            for (int i = rowRange.first; i < rowRange.second + 1; i++)
            {
                for (int j = colRange.first; j < colRange.second + 1; j++)
                {   
                    int newGValue = currentNode.g + 1;
                    
                    //if (isUnblocked(grid, nodes[i][j].coordinates) && (newGValue < nodes[i][j].g))
                    if (nodes[i][j].isUnblocked)
                    {
                        if (newGValue < nodes[i][j].g)
                        {
                            nodes[i][j].parent = currentNode.coordinates;
                            nodes[i][j].g = newGValue;
                            //nodes[i][j].f = newGValue + determineHeuristic(destinationPoints, std::pair(i, j));
                            nodes[i][j].f = newGValue + determineHeuristic(std::pair(i, j));
                            //if (!isItemInList(visitedNodeCoordinates, nodes[i][j].coordinates))
                            if (!nodes[i][j].beenVisited)
                            {
                                priorityQueue.push(nodes[i][j]);
                                nodes[i][j].beenVisited = true;
                                //visitedNodeCoordinates.push_back(nodes[i][j].coordinates);
                            }
                        }
                    }
                }
            }
        }
    }

    return route;
}

void CLI(std::vector<std::vector<uint8_t>> &grid, std::vector<Pair> &srcPoints, std::vector<Pair> &route)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            std::string s;

            if (i == ROW - 1)
            {
                s = 'D'; 
            }
            else if (isItemInList(srcPoints, std::pair(i, j)))
            {
                s = 'S';
            }
            else if (isItemInList(route, std::pair(i, j)))
            {
                s = "\033[31mR\033[0m";
            }
            else
            {
                //s = std::to_string(grid[i][j]);
                s = (grid[i][j] == 1) ? " " : "#";
            }

            std::cout << s;

        }
        std::cout << std::endl;

    }
}

//Starts a* search
//Startrow is the first row in grid
//Destination is the last row in the grid
//Returns a vector with the Pair points that make up the route, in descending order.
std::vector<Pair> aStarSearch(std::vector<std::vector<uint8_t>> &grid)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Pair> srcPoints;

    for (int i = 0; i < ROW; i++)
    {
        Pair point = std::pair(0, 0);
        if (isUnblocked(grid, point))
        {
            srcPoints.push_back(point);
        }
    }
    
    std::vector<Pair> route = findRoute(grid, srcPoints);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    #ifdef __PRINT_ENABLED__
    CLI(grid, srcPoints, route);
    #endif

    std::cout << "runtime: " << duration.count() << std::endl;

    return route;

}

int main() 
{
    std::cout << "A* start" << std::endl;

    std::vector<std::vector<uint8_t>> grid(ROW, std::vector<uint8_t>(COL));

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::mt19937 generator (seed);

            grid[i][j] = generator() % 2;

        }
    }

    for (int i = 0; i < ROW; i++)
    {
        grid[0][i] = 1;
        grid[ROW - 1][i] = 1;
    }

    std::cout << "seeek and destroy !!" << std::endl;
    
    std::vector<Pair> gaming = aStarSearch(grid);


    std::cout << "A* end" << std::endl;
    return 0;
}