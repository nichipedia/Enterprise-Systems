#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX 2000000

/*
 * Prints all primes less than MAX using the Sieve of Eratosthenes.
 */

unsigned * primeGenerator()
{
    unsigned i, j;
    unsigned * primes = malloc(sizeof(unsigned)*MAX);
    for (unsigned i = 0; i < MAX; i++)
    {
        primes[i] = 1;
    }
    for (i = 2; i<MAX; i++)
    {
        j = i*i;
        while(j<MAX)
        {
            primes[j] = 0;
            j += i;
        }
    }
   return primes;
}

char *toCharBuffer(int number)
{
    int n = log10(number) + 1;
    char *buffer = malloc(sizeof(char)*n);
    sprintf(buffer, "%d", number);
    return buffer;
}

int isHappy(int number)
{
    int seq, i;
    while(seq != 4)
    {
        char *buffer = toCharBuffer(number);
        for (i, seq = 0; i < strlen(buffer); i++)
        {
            seq += pow(buffer[i], 2); 
        }
        free(buffer);
        if(seq == 1)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    //unsigned * primes = primeGenerator();
    if(isHappy(6))
    {
        printf("yas\n");
    }
    else 
    {
        printf("oh boi\n");
    }
    return 0;
}






