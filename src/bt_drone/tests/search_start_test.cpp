#include <gtest/gtest.h>
#include "bt_drone/search_start.hpp"

class TestExecutionNode : public testing::Test {
protected:
    void SetUp() override {
        
    }
};

TEST_F(TestExecutionNode, SearchStart) {
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SearchStart>("SearchStart");
    auto blackboard = BT::Blackboard::create();

    int area_width = 50;
    int area_height = 90;
    int drone_id = 0;

    static const char* tree_xml = R"(
    <root BTCPP_format="4" >
        <BehaviorTree ID="Main">
            <Sequence name="root">
                <SearchStart/>
            </Sequence>
        </BehaviorTree>
    </root>)";

    blackboard->set("area_height", area_height);
    blackboard->set("area_width", area_width);
    blackboard->set("drone_id", drone_id);

    auto tree = factory.createTreeFromText(tree_xml, blackboard);

    auto status = tree.tickOnce();
    EXPECT_EQ(status, BT::NodeStatus::SUCCESS);
}