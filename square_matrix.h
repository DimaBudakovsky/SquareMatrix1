#ifndef _SQUARE_MATRIX_H_
  #define _SQUARE_MATRIX_H_

enum DataType
{
  INT_TYPE = 0,
  DOUBLE_TYPE = 1,
  COMPLEX_TYPE = 2
};

struct Complex
{
  double m_re;
  double m_im;

  void init(const double re, const double im)
  {
    m_re = re;
    m_im = im;
  }
};

typedef const void* const* const *const ConstPtrMatrix;
typedef void*** PtrMatrix;
typedef const void* const  ConstPtrData;
typedef void* PtrData;

typedef void (*func)(ConstPtrData a, ConstPtrData b, PtrData c); //��������� �� �������� ���� �������� ��� ��������� ��� �������

//�������� �������� ��� ������ ����� ������
void sumInt(ConstPtrData a, ConstPtrData b, PtrData c);
void sumDouble(ConstPtrData a, ConstPtrData b, PtrData c); 
void sumComplex(ConstPtrData a, ConstPtrData b, PtrData c); 

//�������� ��������� ��� ������ ����� ������
void multiplicationInt(ConstPtrData a, ConstPtrData b, PtrData c);  
void multiplicationDouble(ConstPtrData a, ConstPtrData b, PtrData c); 
void multiplicationComplex(ConstPtrData a, ConstPtrData b, PtrData c);

//������� ��������� �������� � ��������� ������
//C = A + B with size NxN
bool getSumMatrix(ConstPtrMatrix A, ConstPtrMatrix B, PtrMatrix C, const int N, func sum_f);
//C = A * B with size NxN
bool getMultMatrix(ConstPtrMatrix A, ConstPtrMatrix B, PtrMatrix C, const int N, func mult_f);

//��������� ������ ��� ������� ��������� ����
PtrMatrix createSquareMatrix(const unsigned int N, const DataType dtype);
//������������ ������ ��� ������� ��������� ����
void freeSquareMatrix(PtrMatrix A, const unsigned int N, const DataType dtype);



#endif //_SQUARE_MATRIX_H_