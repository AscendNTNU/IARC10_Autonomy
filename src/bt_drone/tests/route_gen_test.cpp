#include <gtest/gtest.h>
#include "bt_drone/route_gen.hpp"

class TestExecutionNode : public testing::Test {
protected:
    void SetUp() override {
        
    }
};


TEST_F(TestExecutionNode, GenerateRoute_generates_equal) {
    auto blackboard = BT::Blackboard::create();

    std::vector<Mine<double>> mines = generate_random_mines(MINES);


    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <GenerateRoute mines="{mines}" />
            </Sequence>
        </BehaviorTree>
    </root>)";

    blackboard->set<int>("mines", mines);

    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<GenerateRoute>("GenerateRoute");

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    auto status = tree.tickOnce();

    realworld_to_map(mines);
    std::vector<std::vector<int>> bit_map = dilateMineMap(mine_map, THRESHOLD, RADIUS * SCALING_FACTOR);

    AStar astar;
    astar.setGrid(bit_map);

    ASSERT_EQ(blackboard->get("generated_route"), astar.getRoute());
}

TEST_F(TestExecutionNode, GenerateRoute_returns_failure) {
    auto blackboard = BT::Blackboard::create();

    std::vector<Mine<double>> mines = generate_random_mines(10000);


    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <GenerateRoute mines="{mines}" />
            </Sequence>
        </BehaviorTree>
    </root>)";

    blackboard->set<int>("mines", mines);

    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<GenerateRoute>("GenerateRoute");

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    auto status = tree.tickOnce();
    ASSERT_EQ(BT::NodeStatus::FAILURE, status);
}

TEST_F(TestExecutionNode, GenerateRoute_returns_success) {
    auto blackboard = BT::Blackboard::create();

    std::vector<Mine<double>> mines = generate_random_mines(0);


    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <GenerateRoute mines="{mines}" />
            </Sequence>
        </BehaviorTree>
    </root>)";

    blackboard->set<int>("mines", mines);

    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<GenerateRoute>("GenerateRoute");

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    auto status = tree.tickOnce();
    ASSERT_EQ(BT::NodeStatus::SUCCESS, status);
    ASSERT_TRUE(!blackboard->get("generated_route".empty()));
}