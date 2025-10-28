#include<stdio.h>
#include<stdlib.h>

int main()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move, index = 0, temp;

    printf("Enter the number of Requests\n");
    scanf("%d", &n);

    printf("Enter the Requests sequence\n");
    for(i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position\n");
    scanf("%d", &initial);

    printf("Enter total disk size\n");
    scanf("%d", &size);

    printf("Enter the head movement direction for high (1) and for low (0)\n");
    scanf("%d", &move);

    // Sort the request array
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(RQ[j] > RQ[j + 1])
            {
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    // Find the index where initial fits
    for(i = 0; i < n; i++)
    {
        if(initial < RQ[i])
        {
            index = i;
            break;
        }
    }

    printf("\nHead Movement Directions (C-SCAN):\n");

    // If movement is towards higher value
    if(move == 1)
    {
        for(i = index; i < n; i++)
        {
            printf("Move from %d to %d [Right]\n", initial, RQ[i]);
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Move from last request to end of disk
        printf("Move from %d to %d [Right to End]\n", initial, size - 1);
        TotalHeadMoment += abs(size - 1 - initial);

        // Move from end to start (circular)
        printf("Move from %d to %d [Wrap Around to Start]\n", size - 1, 0);
        TotalHeadMoment += abs(size - 1 - 0);
        initial = 0;

        for(i = 0; i < index; i++)
        {
            printf("Move from %d to %d [Right]\n", initial, RQ[i]);
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    else // If movement is towards lower value
    {
        for(i = index - 1; i >= 0; i--)
        {
            printf("Move from %d to %d [Left]\n", initial, RQ[i]);
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Move from lowest request to 0
        printf("Move from %d to %d [Left to Start]\n", initial, 0);
        TotalHeadMoment += abs(initial - 0);

        // Move from 0 to end (circular)
        printf("Move from %d to %d [Wrap Around to End]\n", 0, size - 1);
        TotalHeadMoment += abs(size - 1 - 0);
        initial = size - 1;

        for(i = n - 1; i >= index; i--)
        {
            printf("Move from %d to %d [Left]\n", initial, RQ[i]);
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    float averageSeekTime = (float)TotalHeadMoment / n;

    printf("\nTotal head movement is %d\n", TotalHeadMoment);
    printf("Average seek time is %.2f\n", averageSeekTime);

    return 0;
}
