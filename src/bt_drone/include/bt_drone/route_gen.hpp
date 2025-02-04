#pragma once

#include "behaviortree_cpp/bt_factory.h"
#include <rclcpp/rclcpp.hpp>
#include "a_star.hpp"

class GenerateRoute : public BT::SyncActionNode
{
public:
    GenerateRoute(const std::string& name, const BT::NodeConfig& config);

    static BT::PortsList providedPorts();

    BT::NodeStatus onTick() override;

private:
};