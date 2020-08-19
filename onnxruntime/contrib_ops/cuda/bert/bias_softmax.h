// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "gsl/gsl"
#include "core/providers/cuda/cuda_common.h"

namespace onnxruntime {
namespace contrib {
namespace cuda {

using namespace onnxruntime::cuda;

template <typename input_t, typename output_t, typename acc_t>
void dispatch_bias_softmax_forward(
  output_t* output, 
  const input_t* input, 
  const input_t* input_bias, 
  int element_count, 
  int batch_count, 
  int batch_stride, 
  int bias_repeat_count);

template <typename T>
class BiasDropoutSoftmax final : public CudaKernel {
 public:
  BiasDropoutSoftmax(const OpKernelInfo& info) : CudaKernel{info} {
    info.GetAttrOrDefault("softmax_axis", &softmax_axis_, static_cast<int64_t>(1));
    info.GetAttrOrDefault("broadcast_axis", &broadcast_axis_, static_cast<int64_t>(1));
  }

  Status ComputeInternal(OpKernelContext* context) const override;

 private:
  int64_t softmax_axis_;
  int64_t broadcast_axis_;
};

}  // namespace cuda
}  // namespace contrib
}  // namespace onnxruntime
