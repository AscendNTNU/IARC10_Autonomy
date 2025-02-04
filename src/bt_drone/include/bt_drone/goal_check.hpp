#pragma once

#include "behaviortree_ros2/bt_topic_sub_node.hpp"
#include <std_msgs/msg/Bool.hpp>
#include <behaviortree_cpp/bt_factory.h>

class GoalCheck : public BT::RosTopicSubNode<std_msgs::msg::Bool>
{
public:
    GoalCheck(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params);

    BT::NodeStatus onTick( const std::shared_ptr<sensor_msgs::msg::Bool>& msg) override;
};