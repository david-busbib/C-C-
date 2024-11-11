
#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <iostream>
#include <stdio.h>      /* printf */
#include <cmath>

 #define INDEX_ERROR "INVALID INDEX OF MATRIX"
#define MIN_VALUE 0.1
class Matrix
{
  float *matrix;

  int cols,rows;


 public:
  struct dims
  {
      int  rows,cols;
  };
  /**
   *
   * @struct Dims
   * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
   */
  Matrix ();
  Matrix ( int  , int);
  Matrix (const Matrix&);
  ~Matrix ();
  int get_rows () const;
  int get_cols () const;
  Matrix &transpose ();
  Matrix &vectorize();
  void plain_print() const ;
  Matrix dot(const Matrix&) const;
  float  sum() const;
  float norm() const;
  int  argmax() const;
  Matrix &operator +=(const Matrix&);
  Matrix operator +(const Matrix&) const;
  Matrix &operator =(const Matrix&) ;
  Matrix operator *(const Matrix&) const;
  Matrix operator *(const float&) const;
  friend Matrix  operator *(const float&c,const Matrix&m);
  float operator ()( int i, int j)const ;
  float &operator ()( int i, int j);
  float operator [](int) const;
  friend std::ostream &operator <<(std::ostream &os,const Matrix&matrix_1);
  friend std::istream &operator >>(std::istream &is,const Matrix&matrix_1);
  float &operator[] (int ) ;


 private:
  friend float get_sum (const Matrix &matrix,
                        const float *mat_b,
                        int index_row,
                        int index_col,
                        int b_cols);


};


#endif //MATRIX_H
