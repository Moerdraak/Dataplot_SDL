#pragma once
#include <complex>
#include <iostream>
#include <valarray>
#include "data.h"


using namespace std;
const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

struct MyArray {
    double X; // X axes
    double Y; // Y axes
};

int Time2Freq(TData  * Data, TData *FreqData);
void fft(CArray& x);

//template <class ValType>
complex<double>* FillComp(const double* Data, complex<double>* CData, int Len, int N);
