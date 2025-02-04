#include "goal_check.hpp"
#include <rclcpp/rclcpp.hpp>

GoalCheck::GoalCheck(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : RosTopicSubNode<std_msgs::msg::Bool>(name, conf,params)
{}

BT::NodeStatus GoalCheck::onTick(const std::shared_ptr<std_msgs::msg::Bool>& msg)
{
    bool reachedGoal = msg->data;
    
    if (reachedGoal) return BT::NodeStatus::SUCCESS;

    return BT::NodeStatus::FAILURE;

}

