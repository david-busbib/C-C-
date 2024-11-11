#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

namespace activation
{
     Matrix softmax (const Matrix &matrix);
     Matrix relu (const Matrix &matrix);
}

#endif //ACTIVATION_H
