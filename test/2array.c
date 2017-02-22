#include <stdio.h>
#include <stdlib.h>

#define LIMIT 25 /*size of integers array*/

int main()
{
    int i,j;
    //Malloc stands for memory allocation. Allocates array 
    int *bank = malloc(sizeof(int)*LIMIT);
    int *temp;
    temp = bank;
    for (i=0;i<LIMIT;i++)
    {
        *bank = i;
        bank++; 
    }
    bank = temp;
    for (i=0;i<5;i++)
    {
        for (int j=0; j<5; j++)
        {
            printf("%d ", *bank);
            bank++;
        }
        printf("<- Row %d\n", (i+1));
    }

return 0;
}