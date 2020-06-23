//
// Created by sheffieldwang on 20-6-22.
//

#ifndef FILTER_FFT_H
#define FILTER_FFT_H
#include <math.h>

#define maxn 2048
#define PI acos(-1)



typedef struct
{
    double real;
    double imag;
}
Complex;

Complex c_add(Complex a,Complex b) {Complex c = {a.real + b.real,a.imag + b.imag};return c;}
Complex c_sub(Complex a,Complex b) {Complex c = {a.real - b.real,a.imag - b.imag};return c;}
Complex c_mul(Complex a,Complex b) {Complex c = {a.real*b.real - a.imag*b.imag,a.real*b.imag + a.imag*b.real}; return  c;}
Complex c_abs(Complex a) { Complex c = {a.real*a.real + a.imag * a.imag,0.0}; return c; }

void swap(Complex *a,Complex *b)
{
    Complex temp;
    temp = *a;
    *a = *b;
    *b = temp;
}



Complex* FFT(Complex* a,int n)
{
    //Reverse
    int rev[maxn];
    int len=0,lim = 1;
    while(lim <= n)
        lim <<= 1,len++;
    for(int i = 0; i < lim; ++i)
    {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }

    for(int i = 0; i < lim; ++i)
    {
        if(i < rev[i]) {
            swap(&a[i], &a[rev[i]]);
        }
    }

    //Generate WN and Transform
    for(int dep = 1; dep <= log2(lim);++dep)
    {
        int m = 1 << dep;
        Complex wn  = {cos(2.0 * PI/m),sin(2.0*PI/m)};
        for(int k = 0; k < lim; k+=m)
        {
            Complex w = {1,0};
            for(int j = 0; j< m/2;++j)
            {
                Complex t = c_mul(w,a[k+j+m/2]);
                Complex u = a[k+j];
                a[k+j] = c_add(u,t);
                a[k+j+m/2] = c_sub(u,t);
                w = c_mul(w,wn);
            }
        }
    }
    return a;
}


Complex* IFFT(Complex* a,int n)
{
    //Reverse
    int rev[maxn];
    int len=0,lim = 1;
    while(lim <= n)
        lim <<= 1,len++;
    for(int i = 0; i < lim; ++i)
    {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }

    for(int i = 0; i < lim; ++i)
    {
        if(i < rev[i]) {
            swap(&a[i], &a[rev[i]]);
        }
    }

    //Generate WN and Transform
    for(int dep = 1; dep <= log2(lim);++dep)
    {
        int m = 1 << dep;
        Complex wn  = {cos(2.0 * PI/m),-sin(2.0*PI/m)};
        for(int k = 0; k < lim; k+=m)
        {
            Complex w = {1,0};
            for(int j = 0; j< m/2;++j)
            {
                Complex t = c_mul(w,a[k+j+m/2]);
                Complex u = a[k+j];
                a[k+j] = c_add(u,t);
                a[k+j+m/2] = c_sub(u,t);
                w = c_mul(w,wn);
            }
        }
    }
    for(int i = 0; i < n+1; i++)
        a[i].real /= lim;
    return a;
}





#endif //FILTER_FFT_H
