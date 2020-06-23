//
// Created by sheffieldwang on 20-6-22.
//

#ifndef FILTER_CONV_H
#define FILTER_CONV_H
#include <memory.h>
#include "FFT.h"
#include "Filter_Coff.h"

#define N 128
#define L 128
#define M N-L+1

static int count = 0;

Complex* N_point_append(Complex* h)
{
    static Complex ha[N] = {0.0};
    for(int i = 0; i < N; ++i)
    {
        ha[i].real = (i < hL) * h[i].real;
        ha[i].imag = (i < hL) * h[i].imag;
    }
    return ha;
}

Complex* Nx_point_append(Complex* x)
{


    static Complex xa[maxn/L+1][N] = {0.0};
    for(int i = 0; i < L; ++i)
    {
        xa[count][i].real =  x[i].real;
        xa[count][i].imag =  x[i].imag;
   //    printf("%d,%lf\n",i,xa[count][i].real);
    }
    return xa[count];

}

Complex* overlap_add(Complex* x, Complex* h)
{

    // h append
    Complex* ha = N_point_append(h);
    Complex* H = FFT(h,N-1);


    //a cut and append
    Complex xi[L];
    static Complex y[maxn+M];
    for(int i = 0; i < maxn/L; i++)
    {
        for(int j = 0; j < L; j++)
        {
           xi[j].real = x[i*L + j].real;
           xi[j].imag = x[i*L + j].imag;
        }

        //Yi = Xi*H
        Complex* xia = Nx_point_append(xi);
        count++ ;


        Complex* Xi = FFT(xia,N-1);

        Complex Yi[N] = {0};
        for(int k = 0; k < N; k++) {
            Yi[k] = c_mul(Xi[k], H[k]);
        }


        Complex* yi = IFFT(Yi,N-1);
        for(int j = 0; j < N; j++)
        {
            y[i*L + j] = yi[j];

        }
    }

    return y;

}

Complex* sum(Complex* x, Complex* h)
{

    // h append
    Complex* ha = N_point_append(h);
    Complex* H = FFT(h,N-1);


    //a cut and append
    Complex xi[L];
    static Complex y[maxn+M];
    for(int i = 0; i < maxn/L; i++)
    {
        for(int j = 0; j < L; j++)
        {
            xi[j].real = x[i*L + j].real;
            xi[j].imag = x[i*L + j].imag;
        }

        //Yi = Xi*H
        Complex* xia = Nx_point_append(xi);
        count++ ;


        Complex* Xi = FFT(xia,N-1);

        Complex Yi[N] = {0};
        for(int k = 0; k < N; k++) {
            Yi[k] = c_mul(Xi[k], H[k]);
        }


        Complex* yi = IFFT(Yi,N-1);
        for(int j = 0; j < N; j++)
        {
            y[i*L + j] = yi[j];

        }
    }

    return y;

}

#endif //FILTER_CONV_H
