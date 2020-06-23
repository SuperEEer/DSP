#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "FFT.h"
#include "Signal.h"
#include "Conv.h"
#include "Filter_Coff.h"



int main()
{
    //file
    FILE* signal1 = fopen("signal1.dat", "w");
    FILE* FFT1 = fopen("FFT1.dat","w");
    FILE* IFFT1 = fopen("IFFT1.dat","w");
    FILE* hn = fopen("hn.dat","w");
    FILE* Hn = fopen("Hn.dat","w");
    FILE* yn = fopen("yn.dat","w");
    FILE* res = fopen("res.dat","w");

    //signal
    Complex* x = sin_signal(2,100,2000);
    for(int i = 0; i < maxn; ++i)
    {
        fprintf(signal1,"%lf %.16lf\n",(double)i/maxn,x[i].real);
    }

    //FFT
    Complex* X = FFT(x,maxn-1);
    for(int i = 0; i < maxn; ++i)
    {
        fprintf(FFT1,"%d %.16lf\n",i,X[i].real);
    }


    //IFFT
    Complex* ix = IFFT(X,maxn-1);
    for(int i = 0; i < maxn; ++i)
    {
        fprintf(IFFT1,"%d %.16lf\n",i,ix[i].real);
    }

    //get filter
    Complex* h = filter(hc);
    for(int i = 0; i < hL; ++i)
    {
        fprintf(hn,"%d %.16lf\n",i,h[i].real);
    }

    //H
    Complex* H = FFT(h,hL-1);
    for(int i = 0; i<hL-1;i++)
        H[i] = c_abs(H[i]);
    for(int i = 0; i < hL; ++i)
    {
        fprintf(Hn,"%d %.16lf\n",i,H[i].real);
    }

    //Conv
    Complex* y = overlap_add(x,h);
    for(int i = 0; i < maxn+M; ++i)
    {
        fprintf(yn,"%d %.16lf\n",i,y[i].real);
    }

    //FFT Conv
    Complex* Y = FFT(y,maxn-1);
    for(int i = 0; i<hL-1;i++)
        Y[i] = c_abs(Y[i]);
    for(int i = 0; i < maxn; ++i)
    {
        fprintf(res,"%d %.16lf\n",i,Y[i].real);
    }


    fclose(signal1);
    fclose(FFT1);
    fclose(IFFT1);
    fclose(hn);
    fclose(Hn);
    fclose(yn);
    fclose(res);

    printf("done!");
    return 0;

}
