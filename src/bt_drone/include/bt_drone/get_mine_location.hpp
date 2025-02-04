#pragma once

#include <behaviortree_ros2/bt_service_node.hpp>
#include <rclcpp/rclcpp.hpp>

// Update when service from perseption ready

//#include <perception_things/srv/GetDetectedMines.srv>
#include <std_srvs/srv/trigger.hpp>


using GetMineLocation = std_srvs::srv::Trigger;

class GetMineService : public BT::RosServiceNode<GetMineLocation>
{
public:
  explicit GetMineService(const std::string& name, const BT::NodeConfig& conf,
                          const BT::RosNodeParams& params)
    : RosServiceNode<GetMineLocation>(name, conf, params)
  {}

  static BT::PortsList providedPorts()
  {
    std::cout << "PortsAcsessed " << std::endl;
    return providedBasicPorts({});
  }

  bool setRequest(Request::SharedPtr& request) override;

  BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override;

  virtual BT::NodeStatus onFailure(BT::ServiceNodeErrorCode error) override;

};