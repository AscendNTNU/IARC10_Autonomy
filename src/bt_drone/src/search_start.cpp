#include "bt_drone/search_start.hpp"

SearchStart::SearchStart(const std::string& name, const BT::NodeConfig& config)
    : SyncActionNode(name,config)
{}

BT::PortsList SearchStart::providedPorts()
{
    return { BT::InputPort<int>("area_height"),
             BT::InputPort<int>("area_width"),
             BT::InputPort<int>("drone_id"),
             BT::InputPort<NED>("search_start_pose"),
             BT::OutputPort<NED>("search_start_pose"),
             BT::OutputPort<NED>("search_end_vector"),
             BT::OutputPort<NED>("search_path_vector") };
}

BT::NodeStatus SearchStart::tick()
{
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

    //First search
    if (!start_pose)
    {
        NED
        search_start_pose{0, 0 + drone_id.value(), -6},
        search_end_vector{0, 4 + drone_id.value(), 0},
        search_path_vector{area_height.value(), 0, 0};
        setOutput("search_start_pose", search_start_pose);
        setOutput("search_end_vector", search_end_vector);
        setOutput("search_path_vector", search_path_vector);

    } else { //Has already done lawnmower
        
        NED
        search_start_pose{0, start_pose.value().east + 8 + drone_id.value(), -6},
        search_end_vector{0, 4 + search_start_pose.east, 0},
        search_path_vector{area_height.value(), search_start_pose.east, 0};
        setOutput("search_start_pose", search_start_pose);
        setOutput("search_end_vector", search_end_vector);
        setOutput("search_path_vector", search_path_vector);
    } 
}
