#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include "bt_drone/get_mine_location.hpp"

class MineLocationServiceTest : public testing::Test {
protected:
    rclcpp::Node::SharedPtr test_node;

    void SetUp() override {
        rclcpp::init(0, nullptr);
        test_node = std::make_shared<rclcpp::Node>("test_mine_location_service");
    }

    void TearDown() override {
        rclcpp::shutdown();
    }
};

TEST_F(MineLocationServiceTest, ServicePresent) {

    auto service = test_node->create_service<std_srvs::srv::Trigger>(
        "service_test",
        [](const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
        std::shared_ptr<std_srvs::srv::Trigger::Response> response)
        {
            (void)request;
            response->success = true;
            response->message = "Service Call Sucsessful";
        }
    );

    auto blackboard = BT::Blackboard::create();

    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <GetMineService/>
            </Sequence>
        </BehaviorTree>
    </root>)";

    BT::BehaviorTreeFactory factory;

    BT::RosNodeParams params;
    params.nh = test_node;
    params.default_port_value = "service_test";
    factory.registerNodeType<GetMineService>("GetMineService", params);

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    rclcpp::executors::SingleThreadedExecutor exec;
    exec.add_node(test_node);

    // Tick the tree multiple times until success or failure
    BT::NodeStatus status = BT::NodeStatus::RUNNING;
    for (int i = 0; i < 10 && status == BT::NodeStatus::RUNNING; i++) {
        status = tree.tickOnce();
        std::cout << "Ticking tree, current status: " << status << std::endl;
        exec.spin_some(); // Process ROS callbacks
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Allow processing time
    }

    ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    
}