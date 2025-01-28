#include "astar.h"

AStar::AStar(std::vector<std::vector<u_int8_t>> grid)
{
    this->grid = grid;
    this->columns = grid.size();
    this->rows = grid[0].size();

    std::cout << "rows: " << rows << std::endl;
    std::cout << "columns: " << columns << std::endl;
}



//Determines if given point is at the destination
bool AStar::isDestination(Pair point)
{
    return point.second == (this->rows - 1);
}

//Determines if a point on the grid is unblocked or not. 1 is unblocked, 0 is blocked
bool AStar::isUnblocked(std::vector<std::vector<uint8_t>> &grid, Pair point) 
{
    return grid[point.first][point.second] == 1;
}


//Determines lowest H value by computing distance from the last row
int AStar::determineHeuristic(Pair point) 
{
    return point.second - this->rows + 1;
}

//Find range of indices around an index in an array. If it is an edge, return range [edge, index + 1] or [index - 1, edge]
Pair AStar::findRange(int arrayLength, int srcIndex)
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
bool AStar::isItemInList(std::vector<Pair> &list, Pair item)
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

void AStar::createRoute(std::vector<std::vector<Node>> &nodes, Node traceBackNode, std::vector<Pair> &route)
{
    Node currentNode = traceBackNode;

    do
    {
        route.push_back(currentNode.coordinates);
        currentNode = nodes[currentNode.parent.first][currentNode.parent.second];
    }
    while (currentNode.coordinates != currentNode.parent);

}


void AStar::findRoute(std::vector<std::vector<Node>> &nodes, std::vector<Pair> &srcPoints, std::priority_queue<Node> &priorityQueue, std::vector<Pair> &route)
{
    while (!priorityQueue.empty())
    {
        //Choose node with lowest f-value from the priorityQueue
        Node currentNode = priorityQueue.top();


        //CurrentPoint is at destination? return route
        if (isDestination(currentNode.coordinates)) 
        {
            createRoute(nodes, currentNode, route);
            priorityQueue = std::priority_queue<Node>();
        }
        else
        {
            //Find availible parents to node
            Pair rowRange = findRange(this->columns, currentNode.coordinates.first);
            Pair colRange = findRange(this->rows, currentNode.coordinates.second);

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
}

void AStar::initSrcPoints(std::vector<std::vector<uint8_t>> &grid, std::vector<Pair> &srcPoints)
{
    for (int i = 0; i < this->columns; i++)
    {   
        Pair point = std::pair(i, 0);
        if (isUnblocked(grid, point))
        {
            srcPoints.push_back(point);
        }
    }
}

void AStar::initNodes(std::vector<std::vector<uint8_t>> &grid, std::vector<Pair> &srcPoints, 
                std::vector<std::vector<Node>> &nodes, std::priority_queue<Node> &priorityQueue)
{
    // Alle noder blir foreldreløse og har max verdi
    for (int i = 0; i < this->columns; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            std::cout << "yuh: " << i << " " << j << std::endl;
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

    std::cout << "gamger" << std::endl;


    for (Pair point : srcPoints)
    {
        std::cout << "gadgfasdgf" << std::endl;
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

    std::cout << "gaimgerg" << std::endl;
}

//Starts a* search
//Startrow is the first row in grid
//Destination is the last row in the grid
//Returns a vector with the Pair points that make up the route, in descending order.
std::vector<Pair> AStar::aStarSearch(std::vector<std::vector<uint8_t>> &grid)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Pair> srcPoints;


    initSrcPoints(grid, srcPoints);

    std::vector<std::vector<Node>> nodes(columns, std::vector<Node>(rows));

    std::priority_queue<Node> priorityQueue;
    
    initNodes(grid, srcPoints, nodes, priorityQueue);
    std::cout << "gaing" << std::endl;

    //Start searcch!!!!!
    std::vector<Pair> route;

    findRoute(nodes, srcPoints, priorityQueue, route);

    std::cout << "asdfasdfasdf" << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "runtime: " << duration.count() << std::endl;

    return route;

}

void AStar::CLI()
{
    for (int j = 0; j < rows; j++)
    {
        for (int i = 0; i < columns; i++)
        {
            std::string s;
            
            s = (isUnblocked(grid, std::pair(i, j))) ? " " : "#";

            if (j == 0) s = "S";

            if (j == rows - 1) s = "D";

            if (isItemInList(route, std::pair(i, j))) s = "\033[31mR\033[0m";

            std::cout << s;
        }
        std::cout << std::endl;
    }
}

void AStar::runSearch()
{
    AStar::route = aStarSearch(AStar::grid);
}

std::vector<Pair> AStar::getRoute()
{
    return AStar::route;
}