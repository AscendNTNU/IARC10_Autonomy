#pragma once

#include <chrono>
#include <memory>
#include <geometry_msgs/msg/pose.hpp>
#include <rclcpp/rclcpp.hpp>

#include "behaviortree_cpp/bt_factory.h"

class TfCheck : public BT::RosTopicSubNode<transforms::msg::TfInit>
{
public:
    TfCheck(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params);

    static BT::PortsList providedPorts();

    BT::NodeStatus onTick( const std::shared_ptr<transforms::msg::TfInit& last_msg) override;
}