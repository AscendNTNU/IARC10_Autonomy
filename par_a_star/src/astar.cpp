#include "astar.h"

AStar::AStar()
{
    std::vector<std::vector<int>> grid{{0}};
    setGrid(grid);
}

bool AStar::isGridRectangular(std::vector<std::vector<int>> &grid)
{
    int colLength = grid.size();
    int rowLength = grid[0].size();

    for (int i = 0; i < colLength; i++)
    {
        if (grid[i].size() != rowLength) return false;
    }

    return true;
}

int AStar::setGrid(std::vector<std::vector<int>> &grid)
{
    if (grid.empty())
    {
        setErrorMessage("Grid is empty.");
        return 1;
    }

    if (!isGridRectangular(grid)) 
    {
        setErrorMessage("Grid is not rectangular.");
        return 1;
    }

    this->grid = grid;
    this->columns = grid.size();
    this->rows = grid[0].size();

    return 0;
}

void AStar::setErrorMessage(std::string text)
{
    errorMessage = text;
}

//Determines if given point is at the destination
bool AStar::isDestination(Pair point)
{
    return point.second == (this->rows - 1);
}

//Determines if a point on the grid is unblocked or not. 1 is unblocked, 0 is blocked
bool AStar::isUnblocked(std::vector<std::vector<int>> &grid, Pair point) 
{
    return grid[point.first][point.second] == 1;
}

bool AStar::isWithinBounds(Pair point)
{
    if (point.first < 0 || point.first >= columns) return false;
    
    if (point.second < 0 || point.second >= rows) return false;
    
    return true;
}


//Determines lowest H value by computing distance from the last row
int AStar::determineHeuristic(Pair point) 
{
    return point.second - this->rows + 1;
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

    route.push_back(currentNode.coordinates);

}

//Based on wikipedia article of A*
void AStar::findRoute(std::vector<std::vector<Node>> &nodes, std::vector<Pair> &srcPoints, std::priority_queue<Node> &priorityQueue, std::vector<Pair> &route)
{
    int dx[]{0, 1, 0, -1};
    int dy[]{1, 0, -1, 0};

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
            priorityQueue.pop();

            int newGValue = currentNode.g + 1;
            
            for (int k = 0; k < 4; k++)
            {
                int i = currentNode.coordinates.first + dx[k];
                int j = currentNode.coordinates.second + dy[k];

                if(isWithinBounds(std::pair(i, j)))
                {
                    if (nodes[i][j].isUnblocked)
                    {  

                        if(newGValue < nodes[i][j].g)
                        {
                            nodes[i][j].parent = currentNode.coordinates;
                            nodes[i][j].g = newGValue;

                            int h = determineHeuristic(std::pair(i, j));

                            nodes[i][j].h = h;
                            nodes[i][j].f = newGValue + h;
                        
                            if(!nodes[i][j].beenVisited)
                            {
                                priorityQueue.push(nodes[i][j]);
                                nodes[i][j].beenVisited = true;

                            }
                        }
                    }
                }
            }
        }
    }
}

void AStar::initSrcPoints(std::vector<std::vector<int>> &grid, std::vector<Pair> &srcPoints)
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

void AStar::initNodes(std::vector<std::vector<int>> &grid, std::vector<Pair> &srcPoints, 
                std::vector<std::vector<Node>> &nodes, std::priority_queue<Node> &priorityQueue)
{
    // Alle noder blir foreldreløse og har max verdi
    for (int i = 0; i < this->columns; i++)
    {
        for (int j = 0; j < this->rows; j++)
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

    for (Pair point : srcPoints)
    {
        int h = determineHeuristic(point);

        int i = point.first;
        int j = point.second;

        nodes[i][j].g = 0;
        nodes[i][j].h = h;
        nodes[i][j].f = h;
        nodes[i][j].parent = point;
        nodes[i][j].beenVisited = true;

        priorityQueue.push(nodes[i][j]);
    }

}

//Starts a* search
//Startrow is the first row in grid
//Destination is the last row in the grid
//Returns a vector with the Pair points that make up the route, in descending order.
std::vector<Pair> AStar::aStarSearch(std::vector<std::vector<int>> &grid)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Pair> srcPoints;


    initSrcPoints(grid, srcPoints);

    std::vector<std::vector<Node>> nodes(columns, std::vector<Node>(rows));

    std::priority_queue<Node> priorityQueue;
    
    initNodes(grid, srcPoints, nodes, priorityQueue);

    //Start searcch!!!!!
    std::vector<Pair> route;

    findRoute(nodes, srcPoints, priorityQueue, route);


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

int AStar::runSearch()
{
    std::vector<Pair> route = aStarSearch(this->grid);

    this->route = route;

    if (route.empty()) 
    {
        setErrorMessage("Route is empty. Unable to find possible route");
        return 1;
    }

    return 0;
}

std::vector<Pair> AStar::getRoute()
{
    return std::vector<Pair>{this->route};
}

std::string AStar::getErrorMessage()
{
    return errorMessage;
}