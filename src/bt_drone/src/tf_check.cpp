#include "bt_drone/perception_mocker.hpp"


TfCheck::TfCheck(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : RosTopicSubNode<transforms::msg::Tfinit>(name, conf,params)
{}

BT::PortsList BatteryCheck::providedPorts()
{
    return {BT::InputPort<std::string>("transforms", "coordinate transforms")};
}

BT::NodeStatus BatteryCheck::onTick(const std::shared_ptr<transforms::msg::TfInit>& last_msg)
{
    
}