#include "bt_drone/frustumbug.hpp"

FrustumbugAction::FrustumbugAction(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params)
    : BT::RosActionNode<btcpp_ros2_interfaces::action::Sleep>(name, conf, params)
    {}

    bool FrustumbugAction::setGoal(Goal& goal)
    {
        auto wp = getInput<NED>("waypoint");
        goal.msec_timeout = 200; //TODO change to pose when frustembug action
        return true;
    }

    void FrustumbugAction::onHalt()
    {
        RCLCPP_INFO(logger(), "%s: onHalt", name().c_str());
    }

    BT::NodeStatus FrustumbugAction::onResultRecevied(const RosActionNode::WrappedResult &wr)
    {
        RCLCPP_INFO(logger(), "%s: onResultReceived. Done = %s", name().c_str(),
              wr.result->done ? "true" : "false");

        return wr.result->done ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    }

    BT::NodeStatus FrustumbugAction::onFailure(BT::ActionNodeErrorCode error)
    {
        RCLCPP_ERROR(logger(), "%s: onFailure with error: %s", name().c_str(), toStr(error));
        return BT::NodeStatus::FAILURE;
    }

    BT::NodeStatus FrustumbugAction::onFeedback(const std::shared_ptr<NED> feedback)
    {
        NED pose = *feedback;
        auto poselist = getInput<std::list<NED>>("path_logger");
        poselist->push_back(pose);
        
        auto success  = setOutput("path_logger", poselist);
        
        return BT::NodeStatus::RUNNING;
    }
    
    // If want to use plugin to register nodes instead of manually
         //int CreateRosNodePlugin(FrustumbugAction, "FrustumbugAction");