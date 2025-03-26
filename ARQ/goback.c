#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int tf, N, tt, i = 1;

void transmission()
{
    while (i <= tf)
    {
        int z = 0;

        for (int k = i; k < i + N && k <= tf; k++)
        {
            printf("Sending frame %d...\n", k);
            tt++;
        }

        for (int k = i; k < i + N && k <= tf; k++)
        {
            int f = rand() % 2;
            if (!f)
            {
                printf("Ack received for frame %d....\n", k);
                z++;
            }

            else
            {
                printf("Timeout!! Frame Number: %d Not Received\n", k);
                printf("Retransmitting Window...\n");
                break;
            }
        }

        printf("\n");
        i = i + z;
    }
}

int main() {

    srand(time(NULL));
    
    printf("Enter the Total number of frames: ");
    
    scanf("%d", &tf);
    
    printf("Enter the Window Size: ");
    
    scanf("%d", &N);
    
    transmission();
    
    printf("Total number of frames which were sent and resent: %d\n", tt);
    
    return 0;
    
    }
    
    