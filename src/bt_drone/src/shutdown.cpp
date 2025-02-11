#include "bt_drone/shutdown.hpp"

Shutdown::Shutdown(const std::string& name, const BT::NodeConfig& config)
    : SyncActionNode(name,config)
{}

BT::PortsList Shutdown::providedPorts()
{ 
    return { BT::InputPort<std::vector<Pair>>("generated_route"),
             BT::InputPort<int>("area_height"),
             BT::InputPort<int>("area_width"),
             BT::InputPort<int>("drone_id") };
}


BT::NodeStatus Shutdown::onTick()
{
    Pair lastPoint = getInput(<std::vector<Pair>>("generated_route")).back();

    
    //MÅ fly til sluttpunkt hver drone ypipipipip
}