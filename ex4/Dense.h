#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
typedef Matrix (*Activation_func)(const Matrix &matrix);


class Dense{
  Matrix weights, bias;
  Activation_func activation_func;
 public:
  Dense ( const Matrix &weights,const Matrix &bias,
          Activation_func activation_type );
  const Matrix &get_weights() const;
  const Matrix &get_bias() const;
   Activation_func get_activation() const;
  Matrix operator ()( const Matrix&)const;




};
#endif //DENSE_H
