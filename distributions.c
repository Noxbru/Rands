#include <math.h>
#include "rands.h"
#include "distributions.h"

//void box_muller(double *a, double *b, unsigned int (*gen)())
void box_muller(double *a, double *b)
{
    double x,y;
    double r, phi;

    x=(double)RANDS_PREFERRED()/UINT_MAX;
    y=(double)RANDS_PREFERRED()/UINT_MAX;

    r=sqrt(-2*log(x));
    phi=2*M_PI*(y);

    *a=r*cos(phi);
    *b=r*sin(phi);
}

void polar_method(double *a, double *b)
{
    double x,y;
    double s,r;

    do
    {
        x=((double)RANDS_PREFERRED()/(UINT_MAX>>1)-1);
        y=((double)RANDS_PREFERRED()/(UINT_MAX>>1)-1);
        s=x*x+y*y;
    } while(s>=1 || s==0);

    r=sqrt(-2*log(s)/s);
    *a=x*r;
    *b=y*r;
}

unsigned int poisson(double mean)
{
    unsigned int r;
    double x;

    r=0;
    x=1;

    do
    {
        x*=(double)RANDS_PREFERRED()/UINT_MAX;
        r++;
    }while(x>exp(-mean));
    
    return r-1;
}

double chi2(unsigned int n)
{
    unsigned int i;
    double x;

    x=1;
    for(i = 0; i < n/2; i++)
        x*=(double)RANDS_PREFERRED()/UINT_MAX;

    x=-2*log(x);

    if(n%2)
    {
        double a,b;
        polar_method(&a,&b);
        return x+a*a;
    }
    else
        return x;
}

unsigned int binomial(double p, unsigned int n)
{
    unsigned int i;
    unsigned int x;

    x=0;
    for(i = 0; i < n; i++)
    {
        if(((double)RANDS_PREFERRED()/UINT_MAX)<p)
            x++;
    }

    return x;
}

unsigned int binomial_un(unsigned int p, unsigned int n)
{
    unsigned int i;
    unsigned int x;

    x=0;
    for(i = 0; i < n; i++)
    {
        if(RANDS_PREFERRED()<p)
            x++;
    }

    return x;
}
