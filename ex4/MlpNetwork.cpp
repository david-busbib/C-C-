#include "MlpNetwork.h"
#define DIG_N 10
#define RELU_WIEGTHS_ERROR "Error:there is a problem in your wieght or relu"
/**
 * Constructor of Mlp
 * @param weights pointer to array of 4 Matrix
 * @param biases pointer to array of 4 Matrix
 */
MlpNetwork ::MlpNetwork (Matrix *weights, Matrix *bias) : weights(weights),
                                                          bias(bias)
{
  for (int i=0;i<4;++i){
    if (weights[i].get_rows() != weights_dims[i].rows ||
        weights[i].get_cols() != weights_dims[i].cols ||
        bias[i].get_cols()!= bias_dims[i].cols ||
        bias[i].get_rows() != bias_dims[i].rows){
      throw std ::domain_error(RELU_WIEGTHS_ERROR);
    }

  }
}
/**
 * operator () -
 * get an image and return the digit with
 * the highest pr that in that image hitself
 * @param  Matrix of the image
 * @return digit with value
 */
digit MlpNetwork ::operator() (const Matrix &matrix_1)
{
  Matrix d(matrix_1.get_rows(),matrix_1.get_cols());
  d=matrix_1;
  d.vectorize();
  if (d.get_cols()!=1 || d.get_rows() !=(img_dims
  .rows*img_dims.cols)){
    throw std ::length_error(INDEX_ERROR);
  }
  digit m={0,0};
  Dense r1(weights[0],bias[0],activation::relu);
  Dense r2(weights[1],bias[1],activation::relu);
  Dense r3(weights[2],bias[2],activation::relu);
  Dense r4(weights[3],bias[3],activation::softmax);
  Matrix x_1= r1(d);
  Matrix x_2=r2(x_1);
  Matrix x_3=r3(x_2);
  Matrix x_4=r4(x_3);
  //change the digit
  for (int i=0;i<DIG_N;i++){
    if (x_4[i]>m.probability){
      m.probability=x_4[i];
      m.value=i;
    }
  }
  return m;
}