//
// Created by sheffieldwang on 20-6-22.
//

#ifndef FILTER_SIGNAL_H
#define FILTER_SIGNAL_H
#include "FFT.h"


Complex* sin_signal(double A,double fc, double fs) {
/*
 * @parameter A:振幅
 * @parameter fc:频率(int 型)
 * @parameter fs:采样频率(2000HZ)
 */
    double t,s;
    static Complex signal[maxn];
    for (int i = 0; i < maxn; ++i) {
        t = i /fs; //采集时间=采样点数/采样率
        s = A * sin(2 * PI * fc * t);
        signal[i].real = s;
        signal[i].imag = 0.0;
    }
    return signal;
}


Complex* square_signal(double A, double fc,double fs)
{
/*
 * @parameter A:振幅
 * @parameter fc:频率(int 型)
 * @parameter fs:采样频率(2000HZ)
 */
    double t,s;
    static Complex square[maxn];
    for(int i = 0; i < maxn; ++i)
    {
        t = i/fs;
        s = A * sin(2 * PI * fc * t);
        square[i].real = s > 0? A:-A;
        square[i].imag = 0.0;
    }
    return square;
}

#endif //FILTER_SIGNAL_H
