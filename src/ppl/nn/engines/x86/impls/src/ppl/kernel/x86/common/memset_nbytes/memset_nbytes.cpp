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

#include "ppl/kernel/x86/common/internal_include.h"

namespace ppl { namespace kernel { namespace x86 {

ppl::common::RetCode memset_nbytes(
    const void *src,
    const uint64_t bytes_per_element,
    const uint64_t num_elements,
    void* dst)
{
    if (bytes_per_element == 1) {
        const uint8_t val = ((uint8_t*)src)[0];
        PRAGMA_OMP_PARALLEL_FOR()
        for (uint64_t i = 0; i < num_elements; i++) {
            ((uint8_t*)dst)[i] = val;
        }
    } else if (bytes_per_element == 2) {
        const uint16_t val = ((uint16_t*)src)[0];
        PRAGMA_OMP_PARALLEL_FOR()
        for (uint64_t i = 0; i < num_elements; i++) {
            ((uint16_t*)dst)[i] = val;
        }
    } else if (bytes_per_element == 4) {
        const uint32_t val = ((uint32_t*)src)[0];
        PRAGMA_OMP_PARALLEL_FOR()
        for (uint64_t i = 0; i < num_elements; i++) {
            ((uint32_t*)dst)[i] = val;
        }
    } else if (bytes_per_element == 8) {
        const uint64_t val = ((uint64_t*)src)[0];
        PRAGMA_OMP_PARALLEL_FOR()
        for (uint64_t i = 0; i < num_elements; i++) {
            ((uint64_t*)dst)[i] = val;
        }
    } else {
        PRAGMA_OMP_PARALLEL_FOR()
        for (uint64_t i = 0; i < num_elements; i++) {
            for (uint64_t j = 0; j < bytes_per_element; j++) {
                ((uint8_t*)dst)[i * bytes_per_element + j] = ((uint8_t*)src)[j];
            }
        }
    }

    return ppl::common::RC_SUCCESS;
}

}}}; // namespace ppl::kernel::x86
