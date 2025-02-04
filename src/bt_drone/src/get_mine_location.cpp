#include "bt_drone/get_mine_location.hpp"

bool GetMineService::setRequest(Request::SharedPtr& request)
{
    (void)request;
    return true;
}

BT::NodeStatus GetMineService::onResponseReceived(const Response::SharedPtr& response)
{
    std::cout << "onResponseReceived " << std::endl;
    if(response->success)
    {
        RCLCPP_INFO(logger(), "GetMineLocation service succeeded.");
        return BT::NodeStatus::SUCCESS;
    }
    else
    {
        RCLCPP_INFO(logger(), "GetMineLocation service failed: %s", response->message.c_str());
        return BT::NodeStatus::FAILURE;
    }
}

BT::NodeStatus GetMineService::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(logger(), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

