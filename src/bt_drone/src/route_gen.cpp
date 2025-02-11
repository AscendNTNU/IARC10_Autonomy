#include "bt_drone/route_gen.hpp"

GenerateRoute::GenerateRoute(const std::string& name, const BT::NodeConfig& config)
    : SyncActionNode(name, config)
{}

BT::PortsList GenerateRoute::providedPorts()
{
    return { BT::OutputPort<std::vector<Pair>>("generated_route"), //Route which A* have found
             //Minefield_map is the map which will be used to find a route with A* class
             BT::InputPort<std::vector<std::vector<int>>>("minefield_map") };
}


BT::NodeStatus GenerateRoute::onTick()
{
    AStar::AStar astar;
    //if set grid is successful
    if (astar.setGrid(getInput<std::vector<std::vector<int>>>("minefield_map")) == 0)
    {
        //if route is not empty -> success !!!!!!!! :)
        if (!astar.getRoute().empty())
        {
            setOutput<std::vector<Pair>>("generated_route", astar.getRoute());
            
            return BT::NodeStatus::SUCCESS;
        }
    }

    return BT::NodeStatus::FAILURE;
}