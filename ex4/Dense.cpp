#include "Dense.h"

const Matrix &Dense:: get_weights() const
{
  /**
 *
 *
 * @param
 * @return weights
 */
  return weights;
}
const Matrix &Dense:: get_bias() const{
  /**
*
*
* @param
* @return bias
*/
  return bias;
}
/**
*
*
* @param
* @return activation_func
*/
Activation_func Dense:: get_activation() const{

  return activation_func;
}
/**
*
* activate the func
* @param weights,bias,activation_type
* @return
*/
Dense::Dense (const Matrix &weights,const Matrix &bias, Activation_func
activation_type)
    :
    weights(weights), bias(bias),
    activation_func(activation_type)
{
  if (bias.get_rows() != weights.get_rows() || bias.get_cols()!=1){
    throw std ::domain_error(INDEX_ERROR);
  }
}

/**
*
*operator ()
* @param matrix -input
* @return activation_func of (weights * input) + bias using operator + ,*
*/
Matrix Dense::operator() ( const Matrix &input) const
{

  return activation_func((weights * input) + bias);
}
