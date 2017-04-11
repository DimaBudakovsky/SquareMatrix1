#include <stdio.h>

#include "square_matrix.h"
#include "in_out_put.h"

#pragma warning(disable : 4996)

double delta = 1.0/100;

bool compareMatrix(ConstPtrMatrix A, ConstPtrMatrix B, const unsigned int N, const DataType dtype)
{
  bool res = true;
  switch (dtype)
  {
  case INT_TYPE:
    for(unsigned int i = 0; i < N; i++)
      for (unsigned int j = 0; j < N; j++)
        res= res && ( *((int*)A[i][j]) == *((int*)B[i][j]) );

    break;

  case DOUBLE_TYPE:
    for(unsigned int i = 0; i < N; i++)
      for (unsigned int j = 0; j < N; j++)
        res= res && (*((double*)A[i][j]) <= *((double*)B[i][j]) + delta && *((double*)A[i][j]) >= *((double*)B[i][j]) - delta);

    break;

  case COMPLEX_TYPE:
    for(unsigned int i = 0; i < N; i++)
    {
      for (unsigned int j = 0; j < N; j++)
      {
        res= res && (((Complex*)A[i][j])->m_im <= ((Complex*)B[i][j])->m_im + delta && ((Complex*)A[i][j])->m_im >= ((Complex*)B[i][j])->m_im - delta) && 
                    (((Complex*)A[i][j])->m_re <= ((Complex*)B[i][j])->m_re + delta && ((Complex*)A[i][j])->m_re >= ((Complex*)B[i][j])->m_re - delta);
      }
    }

    break;

  default:
    res = false;
    break;
  }

  return res;
}

bool do_sum_test(ConstPtrMatrix A, ConstPtrMatrix B, ConstPtrMatrix C, const unsigned int N, const DataType dtype)
{
  bool res = false;
  PtrMatrix sum_matrix = createSquareMatrix(N, dtype);
  switch (dtype)
  {
  case INT_TYPE:
    res = getSumMatrix(A, B, sum_matrix, N, &sumInt);
    break;
  case DOUBLE_TYPE:
    res = getSumMatrix(A, B, sum_matrix, N, &sumDouble);
    break;
  case COMPLEX_TYPE:
    res = getSumMatrix(A, B, sum_matrix, N, &sumComplex);
    break;
  default:
    break;
  }
  res = res &&compareMatrix(sum_matrix, C, N, dtype);

  freeSquareMatrix(sum_matrix, N, dtype);
  return res;
}

bool do_mult_test(PtrMatrix A, PtrMatrix B, PtrMatrix C, const unsigned int N, const DataType dtype)
{
  bool res = false;
  PtrMatrix mult_matrix = createSquareMatrix(N, dtype);
  switch (dtype)
  {
  case INT_TYPE:
    res = getMultMatrix(A, B, mult_matrix, N, &multiplicationInt);
    break;
  case DOUBLE_TYPE:
    res = getMultMatrix(A, B, mult_matrix, N, &multiplicationDouble);
    break;
  case COMPLEX_TYPE:
    res = getMultMatrix(A, B, mult_matrix, N, &multiplicationComplex);
    break;
  default:
    break;
  }

  res = res && compareMatrix(mult_matrix, C, N, dtype);

  freeSquareMatrix(mult_matrix, N, dtype);
  return res;
}

bool readMatrix(FILE *in, PtrMatrix A, const unsigned int N, const DataType dtype)
{
  if (A == NULL || N == 0)
    return false;

  switch (dtype)
  {
  case INT_TYPE:
    for (unsigned int i = 0; i < N; i++)
      for (unsigned int j = 0; j < N; j++)
      {
        int* a_i_j = (int*)(A[i][j]);
        fscanf_s(in,"%d",a_i_j);
      }

    break;
  case DOUBLE_TYPE:
    for (unsigned int i = 0; i < N; i++)
      for (unsigned int j = 0; j < N; j++)
      {
        double* a_i_j = (double*)(A[i][j]);
        fscanf_s(in,"%lf",a_i_j);
      }
    break;
  case COMPLEX_TYPE:
    for (unsigned int i = 0; i < N; i++)
      for (unsigned int j = 0; j < N; j++)
      {
        Complex* a_i_j = (Complex*)(A[i][j]);
        fscanf_s(in,"%lf+%lfi", &(a_i_j->m_re), &(a_i_j->m_im));
      }

    break;
  default:
    return false;
  }
  return true;
}

bool read_test_file(FILE *in)
{
  bool res = true;
  unsigned int N = 0;
  int type_data = 0;

  fscanf_s(in,"%d%d",&N, &type_data);

  DataType dtype;
  switch (type_data)
  {
  case 0:
    dtype = INT_TYPE;
    break;
  case 1:
    dtype = DOUBLE_TYPE;
    break;
  case 2:
    dtype = COMPLEX_TYPE;
    break;
  default:
    return false;
  }
  PtrMatrix data[4];
  for (unsigned int k = 0; k < 4; k++)
  {
    data[k] = createSquareMatrix(N, dtype);
    res = res && readMatrix(in, data[k], N, dtype);
  }

  if (!res)
    printf("Error reading matrix!\n");
  else
  {
    if (do_sum_test(data[0], data[1], data[2], N, dtype))
      printf("Sum test has been gone successful!\n");
    else
      printf("Warning: Sum test has been gone unsuccessful!\n");

    if (do_mult_test(data[0], data[1], data[3], N, dtype))
      printf("Mult test has been gone successful!\n");
    else
      printf("Warning: Mult test has been gone unsuccessful!\n");
  }

  for (unsigned int k = 0; k < 4; k++)
    freeSquareMatrix(data[k], N, dtype);

  return res;
}

int main()
{
  FILE *pFile=fopen("test_square_mtrix.txt", "rt");
  if (pFile == NULL)
    printf("Error opening file!\n");
  int inx = 1;
  while(!feof(pFile))
  {
    printf("Number Test: %d\n", inx);
    read_test_file(pFile);
    printf("\n");
    inx++;
  }
  fclose(pFile);

  getchar();

  return 0;
}