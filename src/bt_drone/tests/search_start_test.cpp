#include <gtest/gtest.h>
#include "bt_drone/search_start.hpp"

class TestExecutionNode : public testing::Test {
protected:
    void SetUp() override {
        
    }
};

TEST_F(TestExecutionNode, SearchStart_FirstCall) {
    auto blackboard = BT::Blackboard::create();

    int area_width = 50;
    int area_height = 90;
    int drone_id = 0;

    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <SearchStart area_height="{area_height}" 
                             area_width="{area_width}" 
                             drone_id="{drone_id}" 
                             search_start_pose="{search_start_pose}" 
                             search_end_vector="{search_end_vector}" 
                             search_path_vector="{search_path_vector}"/>
            </Sequence>
        </BehaviorTree>
    </root>)";

    blackboard->set<int>("area_height", area_height);
    blackboard->set<int>("area_width", area_width);
    blackboard->set<int>("drone_id", drone_id);

    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SearchStart>("SearchStart");

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    auto status = tree.tickOnce();
    
    NED
    //expected_search_start_pose{0, 0, -6},
    expected_search_end_vector{0, 4, 0},
    expected_search_path_vector{90, 0, 0},
    search_start_pose;

    ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    ASSERT_TRUE(blackboard->get("search_start_pose", search_start_pose));
    EXPECT_EQ(search_start_pose, (NED{0, 0, -6}));
    EXPECT_EQ(blackboard->get<NED>("search_end_vector"), expected_search_end_vector);
    EXPECT_EQ(blackboard->get<NED>("search_path_vector"), expected_search_path_vector);
}

TEST_F(TestExecutionNode, SearchStart_Subcalls) {
    auto blackboard = BT::Blackboard::create();

    int area_width = 50;
    int area_height = 90;
    int drone_id = 0;
    NED search_start_pose = {0, 0, -6};

    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <SearchStart area_height="{area_height}" 
                             area_width="{area_width}" 
                             drone_id="{drone_id}" 
                             search_start_pose="{search_start_pose}" 
                             search_end_vector="{search_end_vector}" 
                             search_path_vector="{search_path_vector}"/>
            </Sequence>
        </BehaviorTree>
    </root>)";

    blackboard->set<int>("area_height", area_height);
    blackboard->set<int>("area_width", area_width);
    blackboard->set<int>("drone_id", drone_id);
    blackboard->set<NED>("search_start_pose", search_start_pose);

    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SearchStart>("SearchStart");

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    auto status = tree.tickOnce();
    
    NED
    expected_search_end_vector{0, 12, 0},
    expected_search_path_vector{90, 8, 0};

    ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    ASSERT_TRUE(blackboard->get("search_start_pose", search_start_pose));
    EXPECT_EQ(search_start_pose, (NED{0, 8, -6}));
    EXPECT_EQ(blackboard->get<NED>("search_end_vector"), expected_search_end_vector);
    EXPECT_EQ(blackboard->get<NED>("search_path_vector"), expected_search_path_vector);
}

TEST_F(TestExecutionNode, SearchStart_Wrong) {
    auto blackboard = BT::Blackboard::create();

    int area_width = 50;
    int area_height = 90;
    int drone_id = 0;
    NED search_start_pose = {0, 0, -6};

    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <SearchStart area_height="{area_height}" 
                             area_width="{area_width}" 
                             drone_id="{drone_id}" 
                             search_start_pose="{search_start_pose}" 
                             search_end_vector="{search_end_vector}" 
                             search_path_vector="{search_path_vector}"/>
            </Sequence>
        </BehaviorTree>
    </root>)";

    blackboard->set<int>("area_height", area_height);
    blackboard->set<int>("area_width", area_width);
    blackboard->set<int>("drone_id", drone_id);
    blackboard->set<NED>("search_start_pose", search_start_pose);

    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SearchStart>("SearchStart");

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    auto status = tree.tickOnce();
    
    NED
    expected_search_end_vector{0, 12, 0},
    expected_search_path_vector{90, 8, 0};

    ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    ASSERT_TRUE(blackboard->get("search_start_pose", search_start_pose));
    bool is = search_start_pose == NED{0,4,-6};
    ASSERT_TRUE(!is);
    //EXPECT_EQ(blackboard->get<NED>("search_end_vector"), expected_search_end_vector);
    //EXPECT_EQ(blackboard->get<NED>("search_path_vector"), expected_search_path_vector);
}