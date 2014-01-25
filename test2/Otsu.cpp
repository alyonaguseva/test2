#include "Otsu.h"
#include "stdafx.h"
typedef unsigned char imageInt;
 
// Определение порога методом Оцу
int otsuThreshold(char *image, int size)
{
  // Проверки на NULL и проч. опустим, чтобы сконцетрироваться
  // на работе метода
 
  // Посчитаем минимальную и максимальную яркость всех пикселей
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
 
  // Гистограмма будет ограничена снизу и сверху значениями min и max,
  // поэтому нет смысла создавать гистограмму размером 256 бинов
  int histSize = max - min + 1;
  int* hist = new int[histSize];
 
  // Заполним гистограмму нулями
  for (int t = 0; t < histSize; t++)
    hist[t] = 0;
 
  // И вычислим высоту бинов
  for (int i = 0; i < size; i++)
    hist[image[i] - min]++;
 
  // Введем два вспомогательных числа:
  int m = 0; // m - сумма высот всех бинов, домноженных на положение их середины
  int n = 0; // n - сумма высот всех бинов
  for (int t = 0; t <= max - min; t++)
  {
    m += t * hist[t];
    n += hist[t];
  }
 
  float maxSigma = -1; // Максимальное значение межклассовой дисперсии
  int threshold = 0; // Порог, соответствующий maxSigma
 
  int alpha1 = 0; // Сумма высот всех бинов для класса 1
  int beta1 = 0; // Сумма высот всех бинов для класса 1, домноженных на положение их середины
 
  // Переменная alpha2 не нужна, т.к. она равна m - alpha1
  // Переменная beta2 не нужна, т.к. она равна n - alpha1
 
  // t пробегается по всем возможным значениям порога
  for (int t = 0; t < max - min; t++)
  {
    alpha1 += t * hist[t];
    beta1 += hist[t];
 
    // Считаем вероятность класса 1.
    float w1 = (float)beta1 / n;
    // Нетрудно догадаться, что w2 тоже не нужна, т.к. она равна 1 - w1
 
    // a = a1 - a2, где a1, a2 - средние арифметические для классов 1 и 2
    float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);
    
    // Наконец, считаем sigma
    float sigma = w1 * (1 - w1) * a * a;
 
    // Если sigma больше текущей максимальной, то обновляем maxSigma и порог
    if (sigma > maxSigma)
    {
      maxSigma = sigma;
      threshold = t;
    }
  }
 
  // Не забудем, что порог отсчитывался от min, а не от нуля
  threshold += min;
 
  // Все, порог посчитан, возвращаем его наверх :)
  return threshold;
}