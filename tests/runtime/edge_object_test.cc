// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "ppl/nn/runtime/edge_object.h"
#include "tests/ir/graph_builder.h"
#include "gtest/gtest.h"
using namespace std;
using namespace ppl::nn;
using namespace ppl::nn::test;

class EdgeObjectTest : public testing::Test {
protected:
    void SetUp() override {
        builder_.AddNode("a", ir::Node::Type("test", "op1"), {"input_of_a"}, {"output_of_a"});
        builder_.AddNode("b", ir::Node::Type("test", "op2"), {"output_of_a"}, {"output_of_b"});
        builder_.AddNode("c", ir::Node::Type("test", "op3"), {"output_of_b"}, {"output_of_c"});
        builder_.Finalize();
    }

protected:
    GraphBuilder builder_;
};

TEST_F(EdgeObjectTest, misc) {
    auto topo = builder_.GetGraph()->topo.get();
    auto edge = topo->GetEdgeById(0);
    EXPECT_NE(nullptr, edge);

    EdgeObject object(edge, EdgeObject::T_EDGE_OBJECT);
    EXPECT_EQ(edge, object.GetEdge());
    EXPECT_EQ(EdgeObject::T_EDGE_OBJECT, object.GetObjectType());
}
