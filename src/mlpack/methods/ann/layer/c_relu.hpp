/**
 * @file methods/ann/layer/c_relu.hpp
 * @author Jeffin Sam
 *
 * Implementation of CReLU layer.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_LAYER_C_RELU_HPP
#define MLPACK_METHODS_ANN_LAYER_C_RELU_HPP

#include <mlpack/prereqs.hpp>

#include "layer.hpp"

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * A concatenated ReLU has two outputs, one ReLU and one negative ReLU,
 * concatenated together. In other words, for positive x it produces [x, 0],
 * and for negative x it produces [0, x]. Because it has two outputs,
 * CReLU doubles the output dimension.
 *
 * Note:
 * The CReLU doubles the output size.
 *
 * For more information, see the following.
 *
 * @code
 * @inproceedings{ICML2016,
 *   title  = {Understanding and Improving Convolutional Neural Networks
 *             via Concatenated Rectified Linear Units},
 *   author = {LWenling Shang, Kihyuk Sohn, Diogo Almeida, Honglak Lee},
 *   year   = {2016},
 *   url    = {https://arxiv.org/abs/1603.05201}
 * }
 * @endcode
 *
 * @tparam InputType The type of the layer's inputs. The layer automatically
 *     cast inputs to this type (Default: arma::mat).
 * @tparam OutputType The type of the computation which also causes the output
 *     to also be in this type. The type also allows the computation and weight
 *     type to differ from the input type (Default: arma::mat).
 */
template<typename InputType = arma::mat, typename OutputType = arma::mat>
class CReLUType : public Layer<InputType, OutputType>
{
 public:
  //! Create the CReLU object.
  CReLUType();

  /**
   * Ordinary feed forward pass of a neural network, evaluating the function
   * f(x) by propagating the activity forward through f.
   * Works only for 2D Tensors.
   *
   * @param input Input data used for evaluating the specified function.
   * @param output Resulting output activation.
   */
  void Forward(const InputType& input, OutputType& output);

  /**
   * Ordinary feed backward pass of a neural network, calculating the function
   * f(x) by propagating x backwards through f. Using the results from the feed
   * forward pass.
   *
   * @param input The propagated input activation.
   * @param gy The backpropagated error.
   * @param g The calculated gradient.
   */
  void Backward(const InputType& input, const OutputType& gy, OutputType& g);

  //! Serialize the layer.
  template<typename Archive>
  void serialize(Archive& /* ar */, const uint32_t /* version */);
}; // class CReLUType

// Convenience typedefs.

// Standard CReLU layer.
typedef CReLUType<arma::mat, arma::mat> CReLU;


} // namespace ann
} // namespace mlpack

// Include implementation.
#include "c_relu_impl.hpp"

#endif
