#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include "bt_drone/waypoint_gen.hpp"
#include <tf2/utils.h>

// --------------------------------------------Test for å vite at CMake funker----------------------------------------------
// class WaypointTest : public testing::Test {
//   protected:
//     int test = 1;
// };

// TEST_F(WaypointTest, TestingTest) {
//   EXPECT_EQ(test, 1);
// }

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }

class TestExecutionNode : public testing::Test {
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

  auto tree = factory.createTreeFromText(tree_xml, blackboard);

  // Publish a test message
  

  // Allow subscriptions to process
  rclcpp::spin_some(pose_pub_);

  // Tick the tree
  auto status = tree.rootNode()->executeTick();
  EXPECT_EQ(status, BT::NodeStatus::SUCCESS);
}

int main (int argc, char   **argv) {
  testing::InitGoogleTest(&argc, argv);
  rclcpp::init(argc, argv);
  int result = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return result;
}