#pragma once

#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include <sensor_msgs/msg/battery_state.hpp>
#include <behaviortree_cpp/bt_factory.h>

class BatteryCheck : public BT::RosTopicSubNode<sensor_msgs::msg::BatteryState>
{
public:
    BatteryCheck(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params);

    static BT::PortsList providedPorts();

    BT::NodeStatus onTick( const std::shared_ptr<sensor_msgs::msg::BatteryState>& last_msg) override;
};