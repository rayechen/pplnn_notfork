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

#include "ppl/nn/models/onnx/parsers/parse_batchnormalization_param.h"
#include "ppl/nn/models/onnx/utils.h"

namespace ppl { namespace nn { namespace onnx {

ppl::common::RetCode ParseBatchNormalizationParam(const ::onnx::NodeProto& pb_node, void* arg, ir::Node*,
                                                  ir::GraphTopo*) {
    auto param = static_cast<ppl::nn::common::BatchNormalizationParam*>(arg);
    param->epsilon = utils::GetNodeAttrByKey<float>(pb_node, "epsilon", 1e-5);
    param->momentum = utils::GetNodeAttrByKey<float>(pb_node, "momentum", 0.9);
    return ppl::common::RC_SUCCESS;
}

}}} // namespace ppl::nn::onnx