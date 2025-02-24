#include <gtest/gtest.h>
#include "bt_drone/route_gen.hpp"

class TestExecutionNode : public testing::Test {
protected:
    void SetUp() override {
        
    }
};

TEST_F(TestExecutionNode, SearchStart_FirstCall) {
    auto blackboard = BT::Blackboard::create();

    //int area_width = 50;
    //int area_height = 90;
    //int drone_id = 0;

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
    
    //NED
    ////expected_search_start_pose{0, 0, -6},
    //expected_search_end_vector{0, 4, 0},
    //expected_search_path_vector{90, 0, 0},
    //search_start_pose;

    //ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    //ASSERT_TRUE(blackboard->get("search_start_pose", search_start_pose));
    //EXPECT_EQ(search_start_pose, (NED{0, 0, -6}));
    //EXPECT_EQ(blackboard->get<NED>("search_end_vector"), expected_search_end_vector);
    //EXPECT_EQ(blackboard->get<NED>("search_path_vector"), expected_search_path_vector);
}
