#pragma once

#include <behaviortree_ros2/bt_service_node.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/rclcpp.hpp>

#include "behaviortree_ros2/ros_node_params.hpp"
#include "bt_drone/poseNED.hpp"

//TODO Update when service from perseption ready

//#include <perception_things/srv/GetDetectedMines.hpp>
#include <std_srvs/srv/trigger.hpp>


using GetMineLocation = std_srvs::srv::Trigger;

class GetMineService : public BT::RosServiceNode<GetMineLocation>
{
public:
  explicit GetMineService(const std::string& name, const BT::NodeConfig& conf,
                          const BT::RosNodeParams& params)
    : RosServiceNode<GetMineLocation>(name, conf, params)
  {
  }

  static BT::PortsList providedPorts()
  {
    std::cout << "PortsAccessed " << std::endl;
    return providedBasicPorts({ BT::OutputPort<std::vector<NED>>("mine_location_list"), 
                                  //TODO Change to output type of service
                                });
  }

  bool setRequest(Request::SharedPtr& request) override;

  BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override;

  virtual BT::NodeStatus onFailure(BT::ServiceNodeErrorCode error) override;

  rclcpp::Logger logger() {
    return node_->get_logger();
  }

};
