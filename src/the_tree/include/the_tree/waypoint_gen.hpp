#pragma once

#include "pose2d.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include <geometry_msgs/msg/pose.hpp>

class GenerateWaypoints : public BT::SyncActionNode
{
public:
    GenerateWaypoints(const std::string& name, const BT::NodeConfig& config);

    static BT::PortsList providedPorts();

    BT::NodeStatus tick() override;

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr subscription_;
    Pose2D current_pose;
    bool pos_recived = false;
    BT::SharedQueue<Pose2D> generateWaypoits(const Pose2D& start, const Pose2D& target);
};