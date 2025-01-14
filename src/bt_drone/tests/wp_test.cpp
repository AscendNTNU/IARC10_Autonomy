#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include "waypoint_gen.hpp"

class TestExecutionNode : public ::testing::Test {
protected:
  void SetUp() override {
    rclcpp::init(0, nullptr);
    pose_pub_ = rclcpp::Node::make_shared("test_execution_node");
    publisher_ = pose_pub_->create_publisher<geometry_msgs::msg::Pose>("pose_topic", 10);
  }

  void TearDown() override {
    rclcpp::shutdown();
  }

  rclcpp::Node::SharedPtr pose_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr publisher_;
};

TEST_F(TestExecutionNode, GeneratesWaypoints) {
  // Create factory and register your custom node
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<GenerateWaypoints>("GenerateWaypoints");
  auto blackboard = BT::Blackboard::create();

  geometry_msgs::msg::Pose current_pose;
  current_pose.position.x = 0.0;
  current_pose.position.y = 0.0;
  current_pose.position.z = 4.0;
  current_pose.orientation.w = 0.0;
  current_pose.orientation.z = 0.0;
  current_pose.orientation.y = 0.0;
  current_pose.orientation.x = 0.0;

  Pose2D target_pose;
  target_pose.x = 100.0;
  target_pose.y = 45.0;
  target_pose.theta = 0.0;
  blackboard->set("target_position", target_pose);
  publisher_->publish(current_pose);

  // Create the tree
  static const char* tree_xml = R"(
  <root BTCPP_format="4" >
    <BehaviorTree ID="Main">
      <GenerateWaypoints target_position="{target_pose}">
    </BehaviorTree>
  </root>)";

  auto tree = factory.createTreeFromText(tree_xml);

  // Publish a test message
  

  // Allow subscriptions to process
  rclcpp::spin_some(pose_pub_);

  // Tick the tree
  auto status = tree.rootNode()->executeTick();
  EXPECT_EQ(status, BT::NodeStatus::SUCCESS);
}