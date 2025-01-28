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
        std::vector<std::vector<int>> grid;

        int columns;
        int rows;

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
        

    public:
        AStar(std::vector<std::vector<int>> &grid);

        AStar();

        void setGrid(std::vector<std::vector<int>> &grid);

        int runSearch();

        std::vector<Pair> getRoute();

        void CLI();

};