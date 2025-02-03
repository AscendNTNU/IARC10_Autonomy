#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>

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



class AStar
{
    private:
        std::string errorMessage;

        //grid, indexes with [column number][row]
        std::vector<std::vector<int>> grid;

        //Number of columns in grid
        int columns;

        //Number of rows in grid
        int rows;

        //Route found after A* algo has run
        std::vector<Pair> route;
        
        bool isDestination(Pair point);

        bool isUnblocked(std::vector<std::vector<int>> &grid, Pair point);

        bool isWithinBounds(Pair point);

        int determineHeuristic(Pair point);

        bool isItemInList(std::vector<Pair> &list, Pair item);

        void createRoute(std::vector<std::vector<Node>> &nodes, Node traceBackNode, std::vector<Pair> &route);

        void findRoute(std::vector<std::vector<Node>> &nodes, std::vector<Pair> &srcPoints, 
                        std::priority_queue<Node> &priorityQueue, std::vector<Pair> &route);

        void initSrcPoints(std::vector<std::vector<int>> &grid, std::vector<Pair> &srcPoints);
        
        void initNodes(std::vector<std::vector<int>> &grid, std::vector<Pair> &srcPoints, 
                        std::vector<std::vector<Node>> &nodes, std::priority_queue<Node> &priorityQueue);

        std::vector<Pair> aStarSearch(std::vector<std::vector<int>> &grid);

        bool isGridRectangular(std::vector<std::vector<int>> &grid);

        void setErrorMessage(std::string text);
        

    public:
        //Constructor
        AStar();

        //Sets grid which will be used for A*
        //Grid must be rectangular
        //First row is by default start, last row is destination
        int setGrid(std::vector<std::vector<int>> &grid);

        //Runs A* algo
        int runSearch();

        //Returns route after A* search from startrow to destinationrow
        std::vector<Pair> getRoute();

        void CLI();

        //Returns error message 
        std::string getErrorMessage();

};