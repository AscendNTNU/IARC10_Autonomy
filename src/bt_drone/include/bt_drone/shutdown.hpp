#pragma once

#include "behaviortree_cpp/bt_factory.h"
#include <rclcpp/rclcpp.hpp>
#include "bt_drone/poseNED.hpp"

class Shutdown : public BT::SyncActionNode
{
    public:
    Shutdown(const std::string& name, const BT::NodeConfig& config);

    BT::NodeStatus onTick() override;
};
