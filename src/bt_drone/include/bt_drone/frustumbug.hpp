#pragma once

#include "behaviortree_ros2/bt_action_node.hpp"
#include "bt_drone/poseNED.hpp"
//#include "behaviortree_cpp/bt_factory.h"
//#include "ros_interfaces/action/NEDpose"
#include <rclcpp/rclcpp.hpp>
#include <list>
#include <iostream>

//#include <std.hpp>

#include "btcpp_ros2_interfaces/action/sleep.hpp" //Change to furst

//TODO----------- CHANGE ROS ACTION TO FRUSTEMBUG --------------TODO// 

class FrustumbugAction : public BT::RosActionNode<btcpp_ros2_interfaces::action::Sleep> //Change to action
{
public:
    FrustumbugAction(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
        : BT::RosActionNode<btcpp_ros2_interfaces::action::Sleep>(name, conf, params)
    {}

    static BT::PortsList providedPorts(){
        return providedBasicPorts({ BT::InputPort<NED>("waypoint"),
                                    BT::BidirectionalPort<std::list<NED>>("path_logger")});
    }

    bool setGoal(Goal& goal) override;

    void onHalt() override;

    BT::NodeStatus onResultRecevied(const WrappedResult& wr) override;

    virtual BT::NodeStatus onFailure(BT::ActionNodeErrorCode error) override;

    BT::NodeStatus onFeedback(const std::shared_ptr<NED> feedback) override;
    
};