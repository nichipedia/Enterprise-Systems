#include <stdio.h>
#include <stdlib.h>

#define LIMIT 200000

int * primeSiethe()
{
    int i,j;
    int *primes;
    int z = 1;
    primes = malloc(sizeof(int)*LIMIT);
    for (i=2;i<LIMIT;i++)
    {
        primes[i]=1;
    }
    for (i=2;i<LIMIT;i++)
    {
        if (primes[i]) 
        {
            for (j=i;i*j<LIMIT;j++)
            {
                primes[i*j]=0;
            }
        }
    }
    return primes;
}


int main()
{
   int *primes = primeSiethe();
   for (int i = 0; i < 200000; i++)
   {
       if (primes[i])
       {
           printf("I am %d and I am prime\n", i);
       }
   }
    return 0;
}