#include "Otsu.h"
#include "stdafx.h"
typedef unsigned char imageInt;
 
// ����������� ������ ������� ���
int otsuThreshold(char *image, int size)
{
  // �������� �� NULL � ����. �������, ����� �����������������
  // �� ������ ������
 
  // ��������� ����������� � ������������ ������� ���� ��������
  int min = image[0];
  int max = image[0];
 
  for (int i = 1; i < size; i++)
  {
    int value = image[i];
 
    if (value < min)
      min = value;
 
    if (value > max)
      max = value;
  }
 
  // ����������� ����� ���������� ����� � ������ ���������� min � max,
  // ������� ��� ������ ��������� ����������� �������� 256 �����
  int histSize = max - min + 1;
  int* hist = new int[histSize];
 
  // �������� ����������� ������
  for (int t = 0; t < histSize; t++)
    hist[t] = 0;
 
  // � �������� ������ �����
  for (int i = 0; i < size; i++)
    hist[image[i] - min]++;
 
  // ������ ��� ��������������� �����:
  int m = 0; // m - ����� ����� ���� �����, ����������� �� ��������� �� ��������
  int n = 0; // n - ����� ����� ���� �����
  for (int t = 0; t <= max - min; t++)
  {
    m += t * hist[t];
    n += hist[t];
  }
 
  float maxSigma = -1; // ������������ �������� ������������ ���������
  int threshold = 0; // �����, ��������������� maxSigma
 
  int alpha1 = 0; // ����� ����� ���� ����� ��� ������ 1
  int beta1 = 0; // ����� ����� ���� ����� ��� ������ 1, ����������� �� ��������� �� ��������
 
  // ���������� alpha2 �� �����, �.�. ��� ����� m - alpha1
  // ���������� beta2 �� �����, �.�. ��� ����� n - alpha1
 
  // t ����������� �� ���� ��������� ��������� ������
  for (int t = 0; t < max - min; t++)
  {
    alpha1 += t * hist[t];
    beta1 += hist[t];
 
    // ������� ����������� ������ 1.
    float w1 = (float)beta1 / n;
    // �������� ����������, ��� w2 ���� �� �����, �.�. ��� ����� 1 - w1
 
    // a = a1 - a2, ��� a1, a2 - ������� �������������� ��� ������� 1 � 2
    float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);
    
    // �������, ������� sigma
    float sigma = w1 * (1 - w1) * a * a;
 
    // ���� sigma ������ ������� ������������, �� ��������� maxSigma � �����
    if (sigma > maxSigma)
    {
      maxSigma = sigma;
      threshold = t;
    }
  }
 
  // �� �������, ��� ����� ������������ �� min, � �� �� ����
  threshold += min;
 
  // ���, ����� ��������, ���������� ��� ������ :)
  return threshold;
}