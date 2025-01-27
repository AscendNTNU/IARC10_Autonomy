#include "behaviortree_cpp/bt_factory.h"
#include "bt_drone/poseNED.hpp"

class SearchStart : public BT::SyncActionNode
{
public:
    SearchStart(const std::string& name, const BT::NodeConfig& config);

    static BT::PortsList providedPorts();
    
    BT::NodeStatus tick() override;

};