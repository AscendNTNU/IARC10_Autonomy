#include "frustumbug_sub.hpp"
#include <rclcpp/rclcpp.hpp>

FrustumbugSubscriber::FrustumbugSubscriber(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : RosTopicSubNode<std_msgs::msg::Bool>(name, conf,params)
{}

BT::NodeStatus FrustumbugSubscriber::onTick(const std::shared_ptr<std_msgs::msg::Bool>& msg)
{
    bool reachedGoal = msg->data;
    
    if (reachedGoal) return BT::NodeStatus::SUCCESS;

    return BT::NodeStatus::FAILURE;

}

