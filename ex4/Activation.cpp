#include "Activation.h"

#include <cmath>


Matrix activation::relu (const Matrix &matrix)
{

/**
 * Function that assigng the relu func ,pass in all element if negative
 * change to zero
 * @param matrix_1
 * @return matrix_1
 */
  Matrix matrix_1(matrix.get_rows(),matrix.get_cols());
  for (int i=0;i<matrix.get_cols()*matrix.get_rows();i++){
    if (matrix[i]<0){
      matrix_1[i]=0;
    }
    else{
      matrix_1[i]=matrix[i];}
  }
  return matrix_1;
}
Matrix activation:: softmax(const Matrix &matrix){
  /**
 * Function that assigng the softmax func ,pass in all element and change the
   * element with exp value if the same element
 * @param matrix_1
 * @return matrix_1
 */
  float s=0;
  Matrix matrix_1(matrix.get_rows(), matrix.get_cols());
  for (int i=0;i<matrix.get_cols()*matrix.get_rows();i++){
    matrix_1[i]= std::exp (matrix[i]);
    s+= std::exp (matrix[i]);
  }
  return (1/s)*matrix_1;
}
