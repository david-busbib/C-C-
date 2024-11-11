#include "Matrix.h"

Matrix :: Matrix(){
  /**
 * default Matrix constructor
 */
  cols=1;
  rows=1;
  matrix=new float [1];
  matrix[0]=0;
}
Matrix::Matrix(int row ,int col) :  cols(col),rows(row){
  /**
 *  Matrix constructor with row and col
 * @param rows ,cols
  */
  if (row<=0 || col<=0){
    throw std ::domain_error(INDEX_ERROR);
  }
  this->cols=col;
  this->rows=row;
  int sum =col*row;
  matrix = new float [sum]();
}
Matrix::Matrix(const Matrix& matrix_1 ){
  /**
*  Matrix constructor with a & to a  matrix of type matrix
* @param Matrix
*/
  if (matrix_1.rows <= 0 || matrix_1.cols <= 0){
    throw std ::domain_error(INDEX_ERROR);
  }
  cols=matrix_1.cols;
  rows=matrix_1.rows;
  int sum = cols * rows;
  matrix = new float [sum];
  for (int i=0;i<sum;i++){
    matrix[i]=matrix_1.matrix[i];
  }
}

Matrix::~Matrix(){
  /**
 * Matrix destructor
 * delete allocated memory of matrix
 */
  delete[] this->matrix;
}
int Matrix:: get_rows() const{
  return rows;
}

int Matrix :: get_cols()const{
  /**
 *
 * @return number of cols of the matrix
 */
  return cols;
}

/**
 * function that transpose the matrix,take the cols and became row
 * and so the row became col
 * @return Transposed Matrix
 */
Matrix &Matrix::transpose(){
  float *new_matrix=new float[this->rows * this->cols];
  for (int i=0; i <= rows * cols; i++){
    new_matrix[i]=matrix[i];
  }
  //create new matrix to change the col and row easier
  int new_col=cols;
  int new_row=rows;
  rows=new_col;
  cols=new_row;
  int i=0;
  while (i < rows){
    for (int j =0;j<cols; j++){
      (*this)(i,j) = new_matrix[(i) + (j)* rows];
    }
    ++i;
  }
  delete [] new_matrix;
  return *this;
}
/**
 * function that vectorize the matrix,so the num of  cols became 1
 * and rows became rows*cols
 * @return vectorize Matrix
 */
Matrix & Matrix:: vectorize() {
  int tmp= rows * cols;
  this->rows =tmp;
  cols =1;
  return *this;

}
/**
 * function to print matrix numbers format
 */
void Matrix ::plain_print() const{
  for (int i=0; i < rows; i++){
    for (int j=0;j<cols;j++){
      std::cout<<(*this)(i,j)<<" ";
    }
    std::cout<<'\n';
  }
}
/**
 * Function dot on matrix
 * @param matrix_1
 * @return n- the dot matrix
 */
Matrix Matrix::dot(const Matrix&matrix_1) const{
  if (matrix_1.cols!=cols || matrix_1.rows != rows){
    throw std ::domain_error(INDEX_ERROR);
  }
  Matrix n(rows, cols);
  for (int i=0; i < rows * cols; i++){
    n.matrix[i]=(*this)[i]*matrix_1.matrix[i];
  }
  return n;

}
/**
 * Function sum on matrix ,pass in all element of the matrix and sum it
 * @return sum- the sum of the matrix
 */
float Matrix::sum() const{
  float  sums=0;
  for(int i=0; i < rows * cols; ++i){
    sums+=matrix[i];
  }
  return sums;


}
/**
 * Function norm on matrix, tke all the element of the matrix and multiply him
 * by himself and in the end take sqrt of that sum

 * @return sqrt of the count
 */
float Matrix::norm()const{
  float count=0;
  for (int i=0; i < rows * cols; i++){
    count+=matrix[i]*matrix[i];
  }
  return std::sqrt (count);
}
/**
 * Function argmx on matrix,pass on all the matrix element and find the bigger
 * defult matrix[0] bigger element

 * @return index of the biggest element
 */

int Matrix::argmax()const{
  int index =0;
  float tmp =matrix[0];
  for (int i=0; i < rows * cols; i++){
    if (tmp<matrix[i]){
      tmp= (*this)[i];
      index=i;
    }
  }
  return index;

}
/**
 * operator of +=
 * @param matrix_b
 * @return new matrix that take the last and + her to the new one given
 */
Matrix &Matrix :: operator +=(const Matrix&matrix_b){
  if (matrix_b.rows <= 0 || matrix_b.cols <= 0){
    throw std ::domain_error(INDEX_ERROR);
  }
  if(matrix_b.rows != rows || matrix_b.cols != cols){
    throw std::domain_error(INDEX_ERROR);
  }
  for (int i=0; i < rows; i++){
    for (int j=0;j<cols;j++){
      (*this)(i,j)= (*this)(i,j) + matrix_b(i, j);
    }
  }
  return *this;
}
/**
 * operator +
 * @param b of type Matrix
 * @return Matrix
 */
Matrix Matrix :: operator +(const Matrix&b) const{
  if (b.rows <= 0 || b.cols <= 0){
    throw std ::domain_error(INDEX_ERROR) ;}
  if(b.rows != rows || b.cols != cols){
    throw std::domain_error(INDEX_ERROR);
  }
  Matrix d(rows, cols);
  for (int i=0; i < rows; i++){
    for (int j=0;j<cols;j++){
      d(i,j)= (*this)(i,j)+b.matrix[i*cols+j];
    }
  }
  return d;
}
/**
 * assignment operator, pass in all element in b and assignment them
 *
 * @param a & to b of type Matrix
 * @return instance matrix
 */
Matrix &Matrix:: operator= (const Matrix &b) {

  if (this !=&b){
    this->cols=b.cols;
    this->rows=b.rows;
    delete []this->matrix;
    matrix= new float[b.cols*b.rows];
    for (int i=0;i<b.cols*b.rows; i++){
      this->matrix[i]=b.matrix[i];

    }
  }
  return *this;
}
/**
 * operator of multiply -
 * multiply two matrix by the law of matrix
 * @param matrix_b
 * @return new matrix matrix
 */
Matrix Matrix:: operator *(const Matrix&matrix_b) const{
  if (matrix_b.rows != cols){
    throw std ::domain_error(INDEX_ERROR);
  }
  Matrix d(rows, matrix_b.cols);
  for (int i=0; i < rows; i++){
    for (int j=0; j < matrix_b.cols; j++){
      d.matrix[i * matrix_b.cols + j]= get_sum (
          (*this), matrix_b.matrix, j, matrix_b.cols, i);
    }
  }
  return d;
}
/**
 * operator of multiply -
 * multiply  matrix by scalar
 * @param float
 * @return matrix
 */
Matrix Matrix:: operator *(const float&c) const{
  Matrix d(rows, cols);
  for (int i=0;i< cols * rows; i++){
    d[i]=(*this)[i]*c;
  }
  return d;
}
/**
 * operator of multiply -
 * multiply  scalar by matrix
 * @param float ,m matrix
 * @return matrix
 */
Matrix  operator *(const float&c,const Matrix&m) {
  return m*c;
}
/**
 * operator () -
 * (a,b) -> return matrix[a][b]
 * @param  row, col
 * @return the value of the matrix in matrix[a][b]
 */
float Matrix:: operator ()( int a, int b)const{
  if (a >= rows || b >= cols){
    throw std ::out_of_range(INDEX_ERROR);
  }
  if (a<0 ||b<0){
    throw std ::out_of_range(INDEX_ERROR);
  }
  return matrix[a*cols+b];
}
/**
 * operator () -
 * (a,b) -> return matrix[a][b]
 * @param  row, col
 * @return  reference to the value of the matrix in matrix[a][b]
 */
float &Matrix:: operator ()( int a, int b){
  if (a >= rows || b >= cols){
    throw std ::out_of_range(INDEX_ERROR);
  }
  if (a<0 ||b<0){
    throw std ::out_of_range(INDEX_ERROR);
  }
  return (float &)matrix[a*cols+b];
}
/**
 * operator [] of Matrix-
 * get Matrix element in index b
 * @param int
 * @return element in place b,if valid alse return error
 *
 */
float Matrix::operator[] (int b) const
{
  if (b >= rows * cols || b < 0){
    throw std ::out_of_range(INDEX_ERROR);
  }
  return matrix[b];
}
/**
 * operator [] of Matrix-
 * get Matrix element in index b
 * @param int
 * @return  reference to the element in place b,if valid alse return error
 *
 */

float &Matrix::operator[] (int b)
{
  if (b >= rows * cols || b < 0){
    throw std ::out_of_range(INDEX_ERROR);
  }
  return (float &)matrix[b];
}
/**
 * output stream operator
 * @param os std::ostream, matrix Matrix
 * @return os
 */
std::ostream &operator <<(std::ostream &os,const Matrix&matrix_1){
  for (int i=0;i<matrix_1.rows; i++){
    for (int j=0;j<matrix_1.cols;j++){
      if (matrix_1(i,j) >
          MIN_VALUE){
        os<<"**";
      }
      else{
        os<<"  ";
      }
    }
    os<<std::endl;
  }
  return os;
}
/**
 *  input operator
 * @param input std::istream, matrix Matrix
 * @return input stream
 */
std::istream &operator >>(std::istream &is,const Matrix&matrix_1){
  if(!is.good()){
    throw std ::runtime_error(INDEX_ERROR);
  }
  float f=0;
  for (int i=0;i<matrix_1.cols*matrix_1.rows; i++){
    if(is.read (reinterpret_cast<char *> (&f),sizeof(float )).fail()){
      throw std ::runtime_error(INDEX_ERROR);
    }
    matrix_1.matrix[i]=f;
  }

  return is;
}
float get_sum (const Matrix &matrix, const float *mat_b, int index_col,int b_cols
    ,  int index_row )
{
  float sum = 0;
  for (int i = 0; i < matrix.cols; ++i)
  {
    sum += ((mat_b[i * b_cols + index_col])*(matrix (index_row, i)) );
  }
  return sum;

}

