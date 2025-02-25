#include "bt_drone/route_gen.hpp"

GenerateRoute::GenerateRoute(const std::string& name, const BT::NodeConfig& config)
    : SyncActionNode(name, config)
{}

BT::PortsList GenerateRoute::providedPorts()
{
    return 
    { 
        BT::InputPort<std::vector<Mine<double>>>("mines"), //List of mines
        BT::OutputPort<std::vector<Pair>>("generated_route") //Route which A* have found
    };
}


BT::NodeStatus GenerateRoute::onTick()
{
    //BT::Expected<std::vector<std::vector<double>>> mines = getInput<std::vector<std::vector<double>>("minefield_map");
    BT::Expected::vector<Mine<double>> mines = getInput<std::vector<Mine<double>>("mines");

    realworld_to_map(mines);

    std::vector<std::vector<double>> mine_map = generateMineMap(mines);
    std::vector<std::vector<int>> bit_map = dilateMineMap(mine_map, THRESHOLD, RADIUS * SCALING_FACTOR);

    Astar astar;

    astar.setGrid(bit_map);
    astar.runSearch();

    std::vector<Pair> route = astar.getRoute();

    if (!route.empty())
    {
        setOutput<std::vector<Pair>>("generated_route", route);
        return BT::NodeStatus::SUCCESS;
    }

    return BT::NodeStatus::FAILURE;
}