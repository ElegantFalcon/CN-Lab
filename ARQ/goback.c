#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tf, tt = 0, N, i = 1;

void transmission()
{

    while (i <= tf)
    {
        int z = 0;

        for (int k = i; k < i + N && k <= tf; k++)
        {
            printf("Sending frame %d \n", k);
            tt++;
        }

        for (int k = i; k < i + N && k <= tf; k++)
        {
            int f = rand() % 2;

            if (!f)
            {
                printf("Frame %d sent succesfully,ack received \n", k);
                z++;
            }

            else
            {
                printf("frame lost %d !! \n", k);
                printf("Retransmitting frame %d ", k);
                break;
            }
        }
        printf("\n");
        i = i + z;
    }
}

void main()
{
    tf = 5;
    N = 3;
    transmission();
}