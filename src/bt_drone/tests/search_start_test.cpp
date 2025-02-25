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
                             lawnmower_queue ="{lawnmower_queue}"/>
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
    expected_search_start_pose{0, 0, 0},
    expected_search_up_path_vector{90, 0, 0},
    expected_search_side_vector{90, 4, 0},
    expected_search_down_path_vector{0, 4, 0},
    search_start_pose;

    using expected_type = BT::SharedQueue<NED>;
    BT::SharedQueue<NED> expected_queue;
    expected_queue->push_back(expected_search_start_pose);
    expected_queue->push_back(expected_search_up_path_vector);
    expected_queue->push_back(expected_search_side_vector);
    expected_queue->push_back(expected_search_down_path_vector);

    auto lawnmower_queue = blackboard->get<BT::SharedQueue<NED>>("lawnmower_queue");

    ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    ASSERT_TRUE(blackboard->get("search_start_pose", search_start_pose));
    EXPECT_EQ(search_start_pose, (NED{0, 0, 0}));
    EXPECT_TRUE((std::is_same_v<decltype(lawnmower_queue), expected_type>));

    //EXPECT_EQ(lawnmower_queue->pop_front(), expected_search_start_pose);
    //EXPECT_EQ(blackboard->get<NED>("search_path_vector"), expected_search_path_vector);
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
                             lawnmower_queue ="{lawnmower_queue}"/>
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

    BT::SharedQueue<NED> test_queue;
    test_queue->push_back(NED{0, 8, 0});
    test_queue->push_back(expected_search_path_vector);
    test_queue->push_back(expected_search_end_vector);

    BT::SharedQueue<NED> node_queue = blackboard->get<BT::SharedQueue<NED>>("lawnmower_queue");

    ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    ASSERT_TRUE(blackboard->get("search_start_pose", search_start_pose));
    EXPECT_EQ(search_start_pose, (NED{0, 8, -6}));
    // EXPECT_EQ(, expected_search_end_vector);
    // EXPECT_EQ(blackboard->get<NED>("search_path_vector"), expected_search_path_vector);
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
                             lawnmower_queue ="{lawnmower_queue}"/>
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

    ASSERT_EQ(status, BT::NodeStatus::SUCCESS);
    ASSERT_TRUE(blackboard->get("search_start_pose", search_start_pose));
    bool is = search_start_pose == NED{0,4,0};
    ASSERT_TRUE(!is);
    //EXPECT_EQ(blackboard->get<NED>("search_end_vector"), expected_search_end_vector);
    //EXPECT_EQ(blackboard->get<NED>("search_path_vector"), expected_search_path_vector);
}