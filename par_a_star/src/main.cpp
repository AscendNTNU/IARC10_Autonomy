#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <queue>
#include <chrono>
#include <random>

#define COL 250
#define ROW 1000

typedef std::pair<int, int> Pair;

struct Node 
{
    //Current placement
    Pair coordinates;

    //Parent node coordinates
    Pair parent;

    //total cost, cost from start, cost to goal
    float f, g, h;

    bool operator<(const Node &obj) const
    {
        return f > obj.f;
    }

};

// Determines if a given point is within bounds
bool isPointWithinBounds(Pair point)
{
    if (point.first > (ROW - 1) || point.first < 0 || point.second > (COL - 1) || point.second < 0)
    {
        return false;
    }

    return true;
}

//Determines if given point is at the destination
bool isDestination(std::vector<Pair> &destinationPoints, Pair point)
{
    for (int i = 0; i < destinationPoints.size(); i++) 
    {
        if (point.first == destinationPoints[i].first && point.second == destinationPoints[i].second)
        {
            return true;
        }
    }
    return false;
}

//Determines if a point on the grid is unblocked or not. 1 is unblocked, 0 is blocked
bool isUnblocked(uint8_t grid[ROW][COL], Pair point) 
{
    return grid[point.first][point.second] == 1;
}


//Determines lowest H value from a given point to a list of destinationPoints
float determineHeuristic(std::vector<Pair> &destinationPoints, Pair point) 
{
    float lowestHValue = __FLT_MAX__;

    for (int i = 0; i < destinationPoints.size(); i++) 
    {
        float hValue = sqrt(pow(point.first - destinationPoints[i].first, 2) + pow(point.second - destinationPoints[i].second, 2));
        lowestHValue = (hValue < lowestHValue) ? hValue : lowestHValue;
    }

    return lowestHValue;
}

//Iterates through a list of points and checks if they are unblocked and within bounds
std::vector<Pair> determineIntraversablePoints(uint8_t grid[ROW][COL], std::vector<Pair> &points)
{
    std::vector<Pair> intraverasblePoints;
    for (int i = 0; i < points.size(); i++)
    {
        if (!isUnblocked(grid, points[i]) || !isPointWithinBounds(points[i]))
        {
            intraverasblePoints.push_back(points[i]);
        }
    }

    return intraverasblePoints;
}

//Removes elements in src that are in remove
template <typename T> 
void removeSharedElements(std::vector<T> &src, std::vector<T> &remove)
{
    for (int i = 0; i < src.size(); i++)
    {
        for (int j = 0; j < remove.size(); j++)
        {
            if (src[i].first == remove[j].first && src[i].second == remove[j].second) 
            { 
                src.erase(src.begin() + i);
            }
        }
    }

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

std::vector<Pair> createRoute(Node nodes[ROW][COL], Node traceBackNode)
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


std::vector<Pair> findRoute(uint8_t grid[ROW][COL], std::vector<Pair> &destinationPoints, std::vector<Pair> &srcPoints)
{
    Node nodes[ROW][COL];

    // Alle noder blir foreldreløse og har max verdi
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            nodes[i][j].f = __FLT_MAX__;
            nodes[i][j].g = __FLT_MAX__;
            nodes[i][j].h = __FLT_MAX__;
            nodes[i][j].parent = std::pair(-1, -1);
            nodes[i][j].coordinates = std::pair(i, j);

        }
    }

    //Initialize nodes to srcPoints
    std::priority_queue<Node> priorityQueue;
    std::vector<Pair> visitedNodeCoordinates;

    for (Pair point : srcPoints)
    {
        int h = determineHeuristic(destinationPoints, point);

        nodes[point.first][point.second].g = 0;
        nodes[point.first][point.second].h = h;
        nodes[point.first][point.second].f = h + 0;
        nodes[point.first][point.second].parent = point;

        //openList.push_back(nodes[point.first][point.second]);
        priorityQueue.push(nodes[point.first][point.second]);
        visitedNodeCoordinates.push_back(nodes[point.first][point.second].coordinates);
    }

    //Start searcch!!!!!
    std::vector<Pair> route;

    while (!priorityQueue.empty())
    {
        //Choose node with lowest f-value from the priorityQueue
        Node currentNode = priorityQueue.top();


        //CurrentPoint is at destination? return route
        if (isDestination(destinationPoints, currentNode.coordinates)) 
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
                    
                    if (isUnblocked(grid, nodes[i][j].coordinates) && (newGValue < nodes[i][j].g))
                    {
                        nodes[i][j].parent = currentNode.coordinates;
                        nodes[i][j].g = newGValue;
                        nodes[i][j].f = newGValue + determineHeuristic(destinationPoints, std::pair(i, j));

                        if (!isItemInList(visitedNodeCoordinates, nodes[i][j].coordinates))
                        {
                            priorityQueue.push(nodes[i][j]);
                            visitedNodeCoordinates.push_back(nodes[i][j].coordinates);
                        }
                    }
                }
            }
        }
    }

    return route;
}

void CLI(uint8_t grid[ROW][COL], std::vector<Pair> &destinationPoints, std::vector<Pair> &srcPoints, std::vector<Pair> &route)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            std::string s;

            if (isItemInList(destinationPoints, std::pair(i, j)))
            {
                s = 'D'; 
            }
            else if (isItemInList(srcPoints, std::pair(i, j)))
            {
                s = 'S';
            }
            else if (isItemInList(route, std::pair(i, j)))
            {
                s = 'R';
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

//std::vector<Pair> aStarSearch(int grid[ROW][COL], std::vector<Pair> destinationPoints, std::vector<Pair> srcPoints)
std::vector<Pair> aStarSearch(uint8_t grid[ROW][COL], std::vector<Pair> &destinationPoints, std::vector<Pair> &srcPoints)
{
    //Which points are invalid
    std::vector<Pair> intraversibleDestinationPoints = determineIntraversablePoints(grid, destinationPoints);
    std::vector<Pair> intraversibleSrcPoints = determineIntraversablePoints(grid, srcPoints);

    //Remove invalid points from original vectors
    removeSharedElements(destinationPoints, intraversibleDestinationPoints);
    removeSharedElements(srcPoints, intraversibleSrcPoints);
    
    std::vector<Pair> route = findRoute(grid, destinationPoints, srcPoints);

    CLI(grid, destinationPoints, srcPoints, route);

    return route;

}

int main() 
{
    std::cout << "A* start" << std::endl;
    //int grid[ROW][COL] = 
        //{
            //{1, 1, 1, 1, 1},
            //{0, 0, 1, 0, 0},
            //{0, 0, 1, 0, 0},
            //{0, 0, 1, 0, 0},
            //{1, 1, 1, 0, 0},
            //{1, 1, 0, 0, 0},
            //{0, 0, 0, 0, 0},
            //{1, 0, 1, 0, 0},
            //{1, 1, 1, 0, 0},
            //{0, 1, 0, 0, 0}
        //};

    //std::vector<Pair> src;
    //for (int i = 0; i < COL; i++)
    //{
        //src.push_back(std::pair(ROW - 1, i));
    //}

    //std::vector<Pair> destination;
    //for (int i = 0; i < COL; i++)
    //{
        //destination.push_back(std::pair(0, i));
    //}
    
    //std::vector<Pair> gaming = aStarSearch(grid, destination, src);

    //std::cout << "route size: " <<  gaming.size() << std::endl;


    uint8_t grid[ROW][COL];
    //int grid[ROW][COL];

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::mt19937 generator (seed);

            grid[i][j] = generator() % 2;
        //int bruh = generator % 2;
            //grid[i][j].push_back(bruh);

            //std::cout << grid[i][j];
        }
        //std::cout << std::endl;
    }

    std::vector<Pair> src;
    for (int i = 0; i < COL; i++)
    {
        src.push_back(std::pair(0, i));
    }

    std::vector<Pair> destination;
    for (int i = 0; i < COL; i++)
    {
        destination.push_back(std::pair(ROW - 1, i));
    }
    
    std::vector<Pair> gaming = aStarSearch(grid, destination, src);



    std::cout << "A* end" << std::endl;
    return 0;
}