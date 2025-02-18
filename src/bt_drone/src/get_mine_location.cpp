#include "bt_drone/get_mine_location.hpp"

bool GetMineService::setRequest(Request::SharedPtr& request)
{
    (void)request;
    std::cout << "Finished setting request, request value: " << request << std::endl;
    return true;
}

BT::NodeStatus GetMineService::onResponseReceived(const Response::SharedPtr& response)
{
    std::cout << "onResponseReceived " << std::endl;
    if(response->success)
    {
        RCLCPP_INFO(logger(), "GetMineLocation service succeeded.");
        
        //Add path logger stuff
        std::string mine_locations = response->message; //TODO Change to output type of service msg
        
        setOutput("mine_location_list", mine_locations);
        
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
    std::cout << "onFailure " << std::endl;
    RCLCPP_ERROR(logger(), "Error: %d", error);
    return BT::NodeStatus::FAILURE;
}

