#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TIMEOUT 3
#define TOTAL_PACKETS 5

int simulate_acknowledgement()
{
    return rand() % 10 < 7;
}

int main()
{
    srand(time(0));

    int packet = 1;
    int ack_received;

    while (packet < TOTAL_PACKETS)
    {
        printf("Sending packet %d....\n", packet);

        sleep(1);
        ack_received = simulate_acknowledgement();

        if (ack_received)
        {
            printf("Ack for packet %d received \n", packet);
            packet++;
        }

        else
        {
            printf("ACK for packet %d lost...Retransmitting \n", packet);
            sleep(TIMEOUT);
        }
    }

    printf("All packet sent succesfully");
    return 0;
}