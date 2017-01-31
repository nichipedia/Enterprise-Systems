#include <stdio.h>
#include <stdlib.h>

int main()
{
    int count = 0;
    for(int i = 0; i < 100;  i++)
    {
        if (isHappy(i) == 1)
        {
            count++;
        }
    }
    printf("This many %d\n", count);
    return 0;
}

int isHappy(int number) 
{
    char numberBank[15];
    int total = 0;
    int temp;
    while (total != 4)
    {
        number = total;
        sprintf(numberBank, "%d", number);
        total = 0;
        for (int i = 0; numberBank[i] != 0; i++)
        {
            temp = numberBank[i] - '0';
            total += (temp * temp);
        }
        if (total == 1)
        {
            return 1;
        }
    }
    return 0;
}


