#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

unsigned MAX;

/*****************************************************************************************************
** Purpose: Generates an array containing all primes less than MAX using the Sieve of Eratosthenes. **
** Return : Returns Memory address of primes array. Index is number. 1 if prime 0 if not.           **
** Params : None.                                                                                   **
*****************************************************************************************************/
short * primeGenerator()
{
    unsigned i, j;
    short * primes = malloc(sizeof(short)*MAX);
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
** Purpose: Determine happy sum of a number for exp.. happySum(123) = 1^2 + 2^2 + 3^2                **
** Return : Happy sum of number passed in..                                                          **
** Params :                                                                                          ** 
**  1) int number -> Number to find happy sum                                                        ** 
******************************************************************************************************/
int happySum(int number)
{
    int sum = 0;
    int n = log10(number) + 1;
    while (number)
    {
        sum += (number%10) * (number%10);
        number /= 10;
    }
    return sum;
}

/******************************************************************************************************
** Purpose: Determine if the  number is happy.                                                       **
** Return : Returns 1 if happy, 0 if not happy.                                                      **
** Params :                                                                                          ** 
**  1) int seq -> "sequnce", Number who's happiness is in question.                                  ** 
******************************************************************************************************/
int isHappy(int seq)
{
    while(seq > 4)
    {
        seq = happySum(seq);
    }
    return seq == 1;
}

short * happyGenerator()
{
    int n = log10(MAX) + 2;
    int limit = 81*n;
    int seq;
    short * happyRef = malloc(sizeof(short)*limit);
    for (int i = 0; i < limit; i++)
    {
        happyRef[i] = 0;
    }
    for (int i = 2; i < limit; i++)
    {
        happyRef[i] = isHappy(i);
    }
    return happyRef;
}

/******************************************************************************************************
** Main Function                                                                                     **
******************************************************************************************************/
int main(int argc, char** argv)
{
    MPI_Init(NULL, NULL);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        printf("Welcome to Happy Prime Generator!\n");
        printf("Please enter your number : ");
        scanf("%d", &MAX);
        printf("\nDetermining Happy Primes up to %d\n", MAX);
        MPI_Bcast(&MAX, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
        clock_t begin = clock();
        short * primes = primeGenerator();
        unsigned n = (MAX/size);
        for (int i = 2; i < n; i++)
        {  
            if (primes[i] && isHappy(i))
            {
                printf("Happy Prime: %d\n", i);
            }
        }
        MPI_Send(&n, 1, MPI_UNSIGNED, (rank+1)%size, 0, MPI_COMM_WORLD);
        MPI_Recv(&n, 1, MPI_UNSIGNED, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        clock_t end = clock();
        double exeTime = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Execution Time: %.2f seconds\n", exeTime);
    }
    else
    {
        MPI_Recv(&MAX, 1, MPI_UNSIGNED, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        short * primes = primeGenerator();
        unsigned n = (MAX/size);
        for (int i = ((rank*n)+1); i < ((rank+1)*n); i++)
        {  
            if (primes[i] && isHappy(i))
            {
                printf("Happy Prime: %d\n", i);
            }
        }
        MPI_Send(&n, 1, MPI_UNSIGNED, (rank+1)%size, 0, MPI_COMM_WORLD);
        MPI_Recv(&n, 1, MPI_UNSIGNED, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Finalize();
    return 0;
}
