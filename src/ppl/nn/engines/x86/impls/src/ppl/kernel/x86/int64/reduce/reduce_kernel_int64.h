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

#ifndef __ST_PPL_KERNEL_X86_INT64_REDUCE_REDUCE_KERNEL_INT64_H_
#define __ST_PPL_KERNEL_X86_INT64_REDUCE_REDUCE_KERNEL_INT64_H_

#include <string.h>
#include <limits.h>
#include <immintrin.h>

#include "ppl/kernel/x86/common/internal_include.h"
#include "ppl/kernel/x86/common/reduce/reduce_common.h"

namespace ppl { namespace kernel { namespace x86 {

template <reduce_op_type_t _op>
inline int64_t reduce_init_val_int64(void)
{
    return 0;
}

template <>
inline int64_t reduce_init_val_int64<REDUCE_MAX>(void)
{
    return INT64_MIN;
}

template <>
inline int64_t reduce_init_val_int64<REDUCE_MIN>(void)
{
    return INT64_MAX;
}

template <>
inline int64_t reduce_init_val_int64<REDUCE_PROD>(void)
{
    return 1;
}

template <reduce_op_type_t _op>
static void reduce_preprocess_int64(
    int64_t *dst,
    int64_t len)
{
    const int64_t init_val = reduce_init_val_int64<_op>();

    PRAGMA_OMP_PARALLEL_FOR()
    for (int64_t i = 0; i < len; i++) {
        dst[i] = init_val;
    }
}

template <reduce_op_type_t _op>
inline int64_t reduce_scalar_kernel_int64(int64_t a, int64_t r);

template <>
inline int64_t reduce_scalar_kernel_int64<REDUCE_MEAN>(int64_t a, int64_t r)
{
    return a + r;
}

template <>
inline int64_t reduce_scalar_kernel_int64<REDUCE_MAX>(int64_t a, int64_t r)
{
    return a > r ? a : r;
}

template <>
inline int64_t reduce_scalar_kernel_int64<REDUCE_MIN>(int64_t a, int64_t r)
{
    return a < r ? a : r;
}

template <>
inline int64_t reduce_scalar_kernel_int64<REDUCE_SUM>(int64_t a, int64_t r)
{
    return a + r;
}

template <>
inline int64_t reduce_scalar_kernel_int64<REDUCE_PROD>(int64_t a, int64_t r)
{
    return a * r;
}

template <reduce_op_type_t _op>
static void reduce_postprocess_int64(
    int64_t *dst,
    int64_t len,
    int64_t div)
{
    if (_op == REDUCE_MEAN) {
        const int64_t rdiv = 1.0f / div;

        PRAGMA_OMP_PARALLEL_FOR()
        for (int64_t i = 0; i < len; i++) {
            dst[i] *= rdiv;
        }
    }
}

}}}; // namespace ppl::kernel::x86

#endif // !__ST_PPL_KERNEL_X86_INT64_REDUCE_REDUCE_KERNEL_INT64_H_