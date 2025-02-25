#pragma once

#include <behaviortree_cpp/bt_factory.h>
#include "bt_drone/poseNED.hpp"

class InitiateBlackboard : public BT::SyncActionNode
{
public:
    InitiateBlackboard(const std::string& name, const BT::NodeConfiguration& config);
    
    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<NED>("waypoint"),
                BT::OutputPort<int>("area_height"),
                BT::OutputPort<int>("area_width"),
                BT::OutputPort<int>("drone_id"),
                BT::OutputPort<int>("minemap_scale")};
    }

    BT::NodeStatus tick() override;
};
