#include <stdlib.h>
#include "square_matrix.h"

void sumInt(ConstPtrData a, ConstPtrData b, PtrData c) 
{
  *((int*)c) = *((int*)a) + *((int*)b);
}


void sumDouble(ConstPtrData a, ConstPtrData b, PtrData c) 
{
  *((double*)c) = *((double*)a) + *((double*)b);
}

void sumComplex(ConstPtrData a, ConstPtrData b, PtrData c) 
{
  Complex a_val = *((Complex*)a);
  Complex b_val = *((Complex*)b);

  ((Complex*)c)->m_re = a_val.m_re + b_val.m_re;
  ((Complex*)c)->m_im = a_val.m_im + b_val.m_im;
}

void multiplicationInt(ConstPtrData a, ConstPtrData b, PtrData c)  
{
  *((int*)c) = *((int*)c) + *((int*)a) * *((int*)b);
}

void multiplicationDouble(ConstPtrData a, ConstPtrData b, PtrData c) 
{
  *((double*)c) = *((double*)c) + *((double*)a) * *((double*)b);
}


void multiplicationComplex(ConstPtrData a, ConstPtrData b, PtrData c) 
{
  Complex a_val = *((Complex*)a);
  Complex b_val = *((Complex*)b);
  Complex c_val_add = *((Complex*)c);

  ((Complex*)c)->init(c_val_add.m_re + a_val.m_re * b_val.m_re - a_val.m_im * b_val.m_im,
    c_val_add.m_im + a_val.m_im * b_val.m_re + a_val.m_re * b_val.m_im);
}


bool getSumMatrix(ConstPtrMatrix A, ConstPtrMatrix B, PtrMatrix C, const int N, func sum_f)
{
  if (A == NULL)
    return false;

  if (B == NULL)
    return false;

  if (C == NULL)
    return false;

  if (sum_f == NULL)
    return false;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      sum_f(A[i][j], B[i][j], C[i][j]);

  return true;
}

static const void*** createBufferMatrix(const unsigned int N)
{
  const void*** A = NULL;
  A = (const void***)malloc(N * sizeof(const void***));
  if (A == NULL)
    return NULL;
  for(unsigned int i = 0; i < N; i++) 
  {
    A[i] = (const void**)malloc(N * sizeof(const void**));
    if (A[i] == NULL)
      return NULL;
  }
  return A;
}

static void freeBufferMatrix(const void*** A, const unsigned int N)
{
  for(unsigned int i = 0; i < N; i++)
    free((const void**) A[i]);

  free((const void***) A);
}

static bool TranspMatrix(ConstPtrMatrix B, const int N, const void*** B_transp)
{
  if (B == NULL)
    return false;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      B_transp[i][j] = B[j][i];

  return true;
}

bool getMultMatrix(ConstPtrMatrix A, ConstPtrMatrix B, PtrMatrix C, const int N, func mult_f)
{
  if (A == NULL)
    return false;

  if (B == NULL)
    return false;

  if (C == NULL)
    return false;

  if (mult_f == NULL)
    return false;

  const void*** B_transp = createBufferMatrix(N);
  bool res = TranspMatrix(B, N, B_transp);

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        mult_f(A[i][k], B_transp[j][k], C[i][j]);

  freeBufferMatrix(B_transp, N);
  return res;
}

PtrMatrix createSquareMatrix(const unsigned int N, const DataType dtype)
{
  PtrMatrix A = NULL;

  if (N == 0)
    return NULL;

  switch (dtype)
  {
  case INT_TYPE:
    A = (PtrMatrix)malloc(N * sizeof(int**));
    if (A == NULL)
      return NULL;
    for(unsigned int i = 0; i < N; i++) 
    {
      A[i] = (PtrData*)malloc(N * sizeof(int*));
      if (A[i] == NULL)
        return NULL;
      for(unsigned int j = 0; j < N; j++)
      {
        A[i][j] = (PtrData)malloc(sizeof(int));
        *((int*)A[i][j]) = 0;
      }
    }
    break;
  case DOUBLE_TYPE:
    A = (PtrMatrix)malloc(N * sizeof(double**));
    if (A == NULL)
      return NULL;
    for(unsigned int i = 0; i < N; i++) 
    {
      A[i] = (PtrData*)malloc(N * sizeof(double*));
      if (A[i] == NULL)
        return NULL;
      for(unsigned int j = 0; j < N; j++)
      {
        A[i][j] = (PtrData)malloc(sizeof(double));
        *((double*)A[i][j]) = 0;
      }
    }
    break;
  case COMPLEX_TYPE:
    A = (PtrMatrix)malloc(N * sizeof(Complex**));
    if (A == NULL)
      return NULL;
    for(unsigned int i = 0; i < N; i++) 
    {
      A[i] = (PtrData*)malloc(N * sizeof(Complex*));
      if (A[i] == NULL)
        return NULL;
      for(unsigned int j = 0; j < N; j++)
      {
        A[i][j] = (PtrData)malloc(sizeof(Complex));
        if (A[i][j] == NULL)
          return NULL;

        ((Complex*)A[i][j])->init(.0,.0);
      }
    }
    break;
  default:
    break;
  }

  return A;
}

void freeSquareMatrix(PtrMatrix A, const unsigned int N, const DataType dtype)
{
  if (A == NULL)
    return;
  switch (dtype)
  {
  case INT_TYPE:
    for(unsigned int i = 0; i < N; i++)
    {
      for(unsigned int j = 0; j < N; j++)
      {
        free((int*) A[i][j]);
      }
      free((int**) A[i]);
    }

    free((int***) A);
    break;
  case DOUBLE_TYPE:
    for(unsigned int i = 0; i < N; i++)
    {
      for(unsigned int j = 0; j < N; j++)
      {
        free((double*) A[i][j]);
      }
      free((double**) A[i]);
    }

    free((double***) A);
    break;
  case COMPLEX_TYPE:
    for(unsigned int i = 0; i < N; i++)
    {
      for(unsigned int j = 0; j < N; j++)
      {
        free((Complex*) A[i][j]);
      }
      free((Complex**) A[i]);
    }

    free((Complex***) A);
    break;
  default:
    break;
  }

}




