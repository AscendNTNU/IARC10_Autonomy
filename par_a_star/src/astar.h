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
        std::vector<std::vector<uint8_t>> grid;

        int columns;
        int rows;

        std::vector<Pair> route;

        bool isDestination(Pair point);

        bool isUnblocked(std::vector<std::vector<uint8_t>> &grid, Pair point);

        int determineHeuristic(Pair point);

        Pair findRange(int arrayLength, int srcIndex);

        bool isItemInList(std::vector<Pair> &list, Pair item);

        void createRoute(std::vector<std::vector<Node>> &nodes, Node traceBackNode, std::vector<Pair> &route);

        void findRoute(std::vector<std::vector<Node>> &nodes, std::vector<Pair> &srcPoints, 
                        std::priority_queue<Node> &priorityQueue, std::vector<Pair> &route);

        void initSrcPoints(std::vector<std::vector<uint8_t>> &grid, std::vector<Pair> &srcPoints);
        
        void initNodes(std::vector<std::vector<uint8_t>> &grid, std::vector<Pair> &srcPoints, 
                        std::vector<std::vector<Node>> &nodes, std::priority_queue<Node> &priorityQueue);

        std::vector<Pair> aStarSearch(std::vector<std::vector<uint8_t>> &grid);

    public:
        AStar(std::vector<std::vector<u_int8_t>> grid);

        void runSearch();

        std::vector<Pair> getRoute();

        void CLI();

};