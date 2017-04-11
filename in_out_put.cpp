#include "in_out_put.h"


void readMatrixFromConsol(PtrMatrix A, const int N, const DataType dtype)
{
  if (A == NULL || N == 0)
    return;

  switch (dtype)
  {
  case INT_TYPE:
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        int* a_i_j = (int*)(A[i][j]);
        scanf_s("%d", a_i_j, sizeof(int));
      }
      printf("\n");
    }

    break;
  case DOUBLE_TYPE:
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        double* a_i_j = (double*)(A[i][j]);
        scanf_s("%lf", a_i_j);
      }
    }


    break;
  case COMPLEX_TYPE:
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        Complex* a_i_j = (Complex*)(A[i][j]);
        scanf_s("%lf+%lfi", &(a_i_j->m_re), &(a_i_j->m_im));
      }
      printf("\n");
    }


    break;
  default:
    break;
  }
}

void printMatrixToConsol(PtrMatrix A, const int N, const DataType dtype)
{
  if (A == NULL || N == 0)
  {
    printf("There is error input print data!");
    return;
  }

  switch (dtype)
  {
  case INT_TYPE:
    printf("Matrix is \n");
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        int* a_i_j = (int*)(A[i][j]);
        printf("%d ", *a_i_j);
      }
      printf("\n");
    }

    break;
  case DOUBLE_TYPE:
    printf("Matrix is \n");
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        double* a_i_j = (double*)(A[i][j]);
        printf("%.4lf ", *a_i_j);
      }
      printf("\n");
    }


    break;
  case COMPLEX_TYPE:
    printf("Matrix is \n");
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        Complex* a_i_j = (Complex*)(A[i][j]);
        printf("%.2lf+%.2lfi ", a_i_j->m_re, a_i_j->m_im);
      }
      printf("\n");
    }


    break;
  default:
    break;
  }
}