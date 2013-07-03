#include <stdio.h>
#include <math.h>
#include "rands.h"
#include "distributions.h"

void calc_mean_var_d(double *mean, double *var, double *data)
{
    unsigned int i;

    *mean=0;
    for(i = 0; i < 50000; i++)
        *mean+=data[i];
    *mean/=50000;

    *var=0;
    for(i = 0; i < 50000; i++)
        *var+=(data[i]-*mean)*(data[i]-*mean);
    *var/=49999;
}

void calc_mean_var_u(double *mean, double *var, unsigned int *data)
{
    unsigned int i;

    *mean=0;
    for(i = 0; i < 50000; i++)
        *mean+=data[i];
    *mean/=50000;

    *var=0;
    for(i = 0; i < 50000; i++)
        *var+=(data[i]-*mean)*(data[i]-*mean);
    *var/=49999;
}

int main(int argc, const char *argv[])
{
    unsigned int i;
    unsigned int r;
    unsigned data1_u[50000];
    unsigned data2_u[50000];
    double r1,r2;
    double mean1, var1;
    double mean2, var2;
    double data1_d[50000];
    double data2_d[50000];

    pr_srand(0);

    printf("#=======================================================================#\n");
    printf("|                      Tests for the distributions                      |\n");
    printf("#=======================================================================#\n");
    printf("#=======================================================================#\n");
    printf("|  The tests consists in generating 50000 random numbers based on the   |\n");
    printf("|   different distributions that are implemented. Then, the mean and    |\n");
    printf("|     the variance are calculated and compared with the theoretical     |\n");
    printf("|                       values that we should get                       |\n");
    printf("|                                                                       |\n");

    for(i = 0; i < 25000; i++)
    {
        box_muller(&r1,&r2);
        data1_d[i*2]=r1;
        data1_d[i*2+1]=r2;
    }
    calc_mean_var_d(&mean1,&var1,data1_d);

    for(i = 0; i < 25000; i++)
    {
        polar_method(&r1,&r2);
        data2_d[i*2]=r1;
        data2_d[i*2+1]=r2;
    }
    calc_mean_var_d(&mean2,&var2,data2_d);

    printf("+-----------------------------------+-----------------------------------+\n");
    printf("| Box-Muller (Normal distribution)  | Polar method (Normal distribution)|\n");
    printf("+-----------------------------------+-----------------------------------+\n");
    printf("| mean:                     %+.4lf | mean:                     %+.4lf |\n",mean1,mean2);
    printf("| variance:                 %+.4lf | variance:                 %+.4lf |\n",var1,var2);
    printf("| mean (theoretical):             0 | mean (theoretical):             0 |\n");
    printf("| variance (theoretical):         1 | variance (theoretical):         1 |\n");
    printf("|                                   |                                   |\n");

    for(i = 0; i < 50000; i++)
    {
        r = poisson(2);
        data1_u[i]=r;
    }
    calc_mean_var_u(&mean1,&var1,data1_u);

    for(i = 0; i < 50000; i++)
    {
        r = poisson(5);
        data2_u[i]=r;
    }
    calc_mean_var_u(&mean2,&var2,data2_u);

    printf("+-----------------------------------+-----------------------------------+\n");
    printf("| Poisson distribution (mean = 2)   | Poisson distribution (mean = 5)   |\n");
    printf("+-----------------------------------+-----------------------------------+\n");
    printf("| mean:                     %+.4lf | mean:                     %+.4lf |\n",mean1,mean2);
    printf("| variance:                 %+.4lf | variance:                 %+.4lf |\n",var1,var2);
    printf("| mean (theoretical):             2 | mean (theoretical):             5 |\n");
    printf("| variance (theoretical):         2 | variance (theoretical):         5 |\n");
    printf("|                                   |                                   |\n");

    for(i = 0; i < 50000; i++)
    {
        r1 = chi2(2);
        data1_d[i]=r1;
    }
    calc_mean_var_d(&mean1,&var1,data1_d);

    for(i = 0; i < 50000; i++)
    {
        r1 = chi2(5);
        data2_d[i]=r1;
    }
    calc_mean_var_d(&mean2,&var2,data2_d);

    printf("+-----------------------------------+-----------------------------------+\n");
    printf("| Chi-Squared (2 degrees of freedom)| Chi-Squared (5 degrees of freedom)|\n");
    printf("+-----------------------------------+-----------------------------------+\n");
    printf("| mean:                     %+.4lf | mean:                     %+.4lf |\n",mean1,mean2);
    printf("| variance:                 %+.4lf | variance:                %+.4lf |\n",var1,var2);
    printf("| mean (theoretical):             2 | mean (theoretical):             5 |\n");
    printf("| variance (theoretical):         4 | variance (theoretical):        10 |\n");
    printf("|                                   |                                   |\n");
    printf("+-----------------------------------+-----------------------------------+\n");

    return 0;
}
