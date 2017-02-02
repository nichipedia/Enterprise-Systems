#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX 2000000

/******************************************************************************************************
 ** Purpose: Generates an array containing all primes less than MAX using the Sieve of Eratosthenes. **
 ** Return : Returns Memory address of primes array. Index is number. 1 if prime 0 if not.           **
 ** Params : None.                                                                                   **
 *****************************************************************************************************/
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

/******************************************************************************************************
** Purpose: Take a number and convert it to a int array.                                             **
** Return : Returns Memory address of int array.                                                     **
** Params:                                                                                           **
**  1) int number -> Number to be converted to int array.                                            **
**  2) int n      -> Length of int array.                                                            **                  
******************************************************************************************************/
int * toIntBuffer(int number, int n)
{
    int i;
    int *buffer = malloc(sizeof(int)*n);
    for ( i = 0; i < n; ++i, number /= 10 )
    {
        buffer[i] = number % 10;
    }
    return buffer;
}

/******************************************************************************************************
** Purpose: Determine if the  number is happy.                                                       **
** Return : Returns 1 if happy, 0 if not happy.                                                      **
** Params :                                                                                          ** 
**  1) int seq -> "sequnce", Number who's happiness is in question.                                  ** 
******************************************************************************************************/
int isHappy(int seq)
{
    int i;
    while(seq != 4)
    {
        int n = log10(seq) + 1;
        int *buffer = toIntBuffer(seq, n);
        seq = 0;
        for (i = 0; i < n; i++)
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

/******************************************************************************************************
** Main Function                                                                                     **
******************************************************************************************************/
int main()
{
    unsigned * primes = primeGenerator();
    for (int i = 2; i < MAX; i++)
    {  
        if (isHappy(i) && primes[i])
        {
            printf("Happy Prime: %d\n", i);
        }
    }
    return 0;
}
