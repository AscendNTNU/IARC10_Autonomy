#include "battery_check.hpp"
#include <rclcpp/rclcpp.hpp>

BatteryCheck::BatteryCheck(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : RosTopicSubNode<sensor_msgs::msg::BatteryState>(name, conf,params)
{}

BT::PortsList BatteryCheck::providedPorts()
{
    return {BT::InputPort<float>("threshold", 20.0, "Battery Threshold")};
}

BT::NodeStatus BatteryCheck::onTick( const std::shared_ptr<sensor_msgs::msg::BatteryState>& last_msg)
{
    float threshold;
    if (!getInput("threshold", threshold))
    {
        throw BT::RuntimeError("Missing input [Threshold]");
    }
    if (last_msg->percentage < threshold)   
    {
        return BT::NodeStatus::FAILURE;
    }
    return BT::NodeStatus::SUCCESS;
    
}