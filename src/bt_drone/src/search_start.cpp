#include "bt_drone/search_start.hpp"
#include <deque>

SearchStart::SearchStart(const std::string& name, const BT::NodeConfig& config)
    : SyncActionNode(name,config)
{}

BT::PortsList SearchStart::providedPorts()
{
    return { BT::InputPort<int>("area_height"),
             BT::InputPort<int>("area_width"),
             BT::InputPort<int>("drone_id"),
             BT::BidirectionalPort<NED>("search_start_pose"),
             BT::OutputPort<BT::SharedQueue<NED>>("lawnmower_queue")};
}

BT::NodeStatus SearchStart::tick()
{
    auto lawnmower_queue = std::make_shared<std::deque<NED>>();
    BT::Expected<int> drone_id = getInput<int>("drone_id");
    BT::Expected<int> area_height = getInput<int>("area_height");
    BT::Expected<int> area_width = getInput<int>("area_width");
    BT::Expected<NED> start_pose = getInput<NED>("search_start_pose");
    
    if (!drone_id || !area_height || !area_width)
    {
        throw BT::RuntimeError("Missing required input [message]: " + 
                                drone_id.error() + ", " + 
                                area_height.error() + ", " + 
                                area_width.error());
    }

    NED search_start_pose;
    NED search_side_vector;
    NED search_up_path_vector;
    NED search_down_path_vector;

    //First search
    if (!start_pose)
    {
        search_start_pose = {0, double(0 + drone_id.value()), 0};
        search_up_path_vector = {double(area_height.value()), 0, 0};
        search_side_vector = {double(area_height.value()), double(4 + drone_id.value()), 0};
        search_down_path_vector = {0, double(4 + drone_id.value()), 0};
        
        
        std::cout << "Initializing new search_start_pose: " << search_start_pose << std::endl;

    } else { //Has already done lawnmower
        
        search_start_pose = {0, start_pose.value().east + 8 + drone_id.value(), 0};
        search_up_path_vector = {double(area_height.value()), start_pose.value().east + 8 + drone_id.value(), 0};
        search_side_vector = {double(area_height.value()), start_pose.value().east + 8 + drone_id.value() + 4, 0};
        search_down_path_vector = {0, start_pose.value().east + 8 + drone_id.value() + 4, 0};
        
        
        std::cout << "Using existing start_pose to compute new values: " << search_start_pose << std::endl;
    }

    auto success = setOutput("search_start_pose", search_start_pose);
    if (!success) {
        std::cerr << "Failed to set search_start_pose in blackboard!" << std::endl;
    }

    lawnmower_queue->push_back(search_start_pose);
    lawnmower_queue->push_back(search_up_path_vector);
    lawnmower_queue->push_back(search_side_vector);
    lawnmower_queue->push_back(search_down_path_vector);

    setOutput("lawnmower_queue", lawnmower_queue);

    
    return BT::NodeStatus::SUCCESS; 
}
