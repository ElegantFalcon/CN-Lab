#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10
#define LOSS_PROBABILITY 20

int send_frame(int frame_number)
{
    printf("Sending frame....%d..\n", frame_number);
    sleep(1);
    int rand_value = rand() % 100;
    if (rand_value < LOSS_PROBABILITY)
    {
        printf("Frame %d lost during transmission.. \n", frame_number);
        return 0;
    }
    else
    {
        printf("Frame sentt....\n");
        return 1;
    }
}

int receive_ack(int frame_number)
{
    printf("Receiving ack for frame ...%d..\n", frame_number);
    sleep(1);
    int rand_value = rand() % 100;
    if (rand_value < LOSS_PROBABILITY)
    {
        printf("Ack %d lost .. \n", frame_number);
        return 0;
    }
    else
    {
        printf("Ack received .. \n");
        return 1;
    }
}

void selective()
{
    int sent_frames[TOTAL_FRAMES] = {0};
    int ack_received[TOTAL_FRAMES] = {0};
    int base = 0;

    while (base < TOTAL_FRAMES)
    {
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
        {
            if (!sent_frames[i])
            {
                sent_frames[i] = send_frame(i);
            }
        }

        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
        {
            if (sent_frames[i] && !ack_received[i])
            {
                ack_received[i] = receive_ack(i);
            }
        }

        while (base < TOTAL_FRAMES && ack_received[base])
        {
            printf("Sliding window forward..Frame %d acknowledged..\n", base);
            base++;
        }
    }

    printf("All frames sent and acknowledged successfully.\n");
}

int main()
{
    srand(time(0)); // Seed random number generator
    selective();
    return 0;
}