#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int normalizeVector(float *x, float *y)
{
     float magnitude;
     float xWork, yWork;
 
     xWork = *x;
     yWork = *y;
 
     magnitude = sqrt(xWork*xWork + yWork*yWork);
     *x = xWork/magnitude;
     *y = yWork/magnitude;
     return 0;
}

int main()
{
     float x, y;
     x = 3;
     y = 4;
     normalizeVector(&x, &y);
     printf("Normalized Vector = ( %.2f, %.2f )\n", x, y);
     return 0;
}
 
 
