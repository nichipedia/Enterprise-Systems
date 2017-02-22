/*****************************************************************************************************
**  Author: w0526207                                                                                **
**  Date: 2/04/17                                                                                   **
*****************************************************************************************************/                
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
    while(seq > 6)
    {
        seq = happySum(seq);
    }
    return seq == 1;
}

/******************************************************************************************************
** Main Function                                                                                     **
** Instructions:                                                                                     **
**  1) To compile use -std=c99 linker                                                                **
**  2) On Leowulf the Please enter number prompt sometimes does not show up.                         **
**     just enter the number and the program will run fine.                                          **
******************************************************************************************************/
int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
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
        for (unsigned i = 2; i < n; i++)
        {  
            if (primes[i] && isHappy(i))
            {
                printf("Happy Prime from process %d: %d\n", rank, i);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
        clock_t end = clock();
        double exeTime = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Execution Time: %.2f seconds\n", exeTime);
    }
    else
    {
        MPI_Bcast(&MAX, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
        short * primes = primeGenerator();
        unsigned n = (MAX/size);
        for (unsigned i = ((rank*n)+1); i < ((rank+1)*n); i++)
        {  
            if (primes[i] && isHappy(i))
            {
                printf("Happy Prime from process %d: %d\n", rank, i);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}