#include "bt_drone/initiate_blackboard.hpp"

InitiateBlackboard::InitiateBlackboard(const std::string& name, const BT::NodeConfiguration& config) : 
    SyncActionNode(name, config) 
{}

BT::NodeStatus InitiateBlackboard::tick()
{
    int area_height = 90;
    int area_width = 50;
    int drone_id = 1;
    NED startpose = {0, 0, 0};
    double scaleMineMap = 10.0;

    if (drone_id == 1 || drone_id == 2)
    {
        startpose = {-2, double(area_width)-double(area_width/drone_id), -4};
    } else if (drone_id == 3 || drone_id == 4)
    {
        startpose = {-2, double(area_width)-double(area_width/drone_id), -4};
    } else {
        std::cout << "Invalid drone id" << std::endl;
        return BT::NodeStatus::FAILURE;
    }
    
    auto success = setOutput("area_height", area_height);
    auto success2 = setOutput("area_width", area_width);
    auto success3 = setOutput("drone_id", drone_id);
    auto success4 = setOutput("waypoint", startpose);
    auto success5 = setOutput("minemap_scale", scaleMineMap);

    if(!success || !success2 || !success3 || !success4 || !success5)
    {
        std::cout << "Could not initiate blackboard, error: " + success.error() + ", " + success2.error() + ", " + success3.error() + ", " + success4.error() << std::endl;
        return BT::NodeStatus::FAILURE;
    }


    return BT::NodeStatus::SUCCESS;
}