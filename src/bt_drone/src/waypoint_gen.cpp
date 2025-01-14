#include "behaviortree_cpp/bt_factory.h"
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <deque>
#include "waypoint_gen.hpp"
#include <tf2/utils.h>

GenerateWaypoints::GenerateWaypoints(const std::string& name, const BT::NodeConfig& config)
    : SyncActionNode(name, config)
{
    //Sub to NavSatFix
    node_ = rclcpp::Node::make_shared("waypoint_gen_node");
    subscription_ = node_->create_subscription<geometry_msgs::msg::Pose>(
        "drone/gps/fix", 10,
        [this](const geometry_msgs::msg::Pose msg)
        {
            current_pose.x = msg.position.x;
            current_pose.y = msg.position.y;
            current_pose.theta = tf2::getYaw(msg.orientation);
            pos_recived = true;
        }
    );
}

BT::PortsList GenerateWaypoints::providedPorts()
{
    return { BT::OutputPort<BT::SharedQueue<Pose2D>>("waypoints"),
             BT::InputPort<Pose2D>("target_position") };
}

BT::NodeStatus GenerateWaypoints::tick()
{
    if (!pos_recived)
    {
        RCLCPP_WARN(node_->get_logger(), "Waiting for current position");
        return BT::NodeStatus::FAILURE;
    }
    Pose2D target_position;
    if(!getInput("target_position", target_position))
    {
        RCLCPP_WARN(node_->get_logger(), "Missing target position");
        return BT::NodeStatus::FAILURE;
    }

    auto waypoints = generateWaypoits(current_pose, target_position);
    setOutput("waypoints", waypoints);

    return BT::NodeStatus::SUCCESS;
}

BT::SharedQueue<Pose2D> GenerateWaypoints::generateWaypoits(const Pose2D& start, const Pose2D& target)
{
    //Make waypoints (1 every 2m)
    auto waypoints = std::make_shared<std::deque<Pose2D>>();

    //Find nr waypoints
    double step_size = 1.5;
    double distance = std::sqrt(((target.x - start.x)*2)+((target.y - start.y)*2));
    int num = static_cast<int>(distance/step_size);
    double waypoint_theta = std::atan2((target.y-start.y),(target.x-start.x));
    
    //Make waypoints 
    for (int i = 0; i < num; i++)
    {
        double waypoint_x = start.x + i * step_size * std::cos(waypoint_theta);
        double waypoint_y = start.y + i * step_size * std::cos(waypoint_theta);

        waypoints->push_back(Pose2D{waypoint_x, waypoint_y, waypoint_theta});
        
    }
    waypoints->push_back(Pose2D{target.x, target.y, waypoint_theta});
    return waypoints;
    
}