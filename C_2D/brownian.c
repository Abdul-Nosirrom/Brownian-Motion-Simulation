#include "brownian.h"

double rand_normal(double mean, double stddev)
{//Box muller method
    static double n2 = 0.0;
    static int n2_cached = 0;
    if (!n2_cached)
    {
        double x, y, r;
        do
        {
            x = 2.0*rand()/RAND_MAX - 1;
            y = 2.0*rand()/RAND_MAX - 1;

            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);
        {
            double d = sqrt(-2.0*log(r)/r);
            double n1 = x*d;
            n2 = y*d;
            double result = n1*stddev + mean;
            n2_cached = 1;
            return result;
        }
    }
    else
    {
        n2_cached = 0;
        return n2*stddev + mean;
    }
}

void generate_data()
{
    int i;
    double totalTime = 0;
    FILE *datafile = fopen("brownian.data", "w");
    double dx, X=0, dt = 0.5;

    for (i=0; i < 1000; i++) {
        dx = sqrt(dt) * rand_normal(0.0, 1.2);
        X += dx;
        fprintf(datafile, "%lf %lf\n", totalTime,X);
        totalTime += dt;
    }

    fclose(datafile);
    
}