#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10
#define LOSS_PROBABILITY 20

int send_frame(int frame_number)
{
    printf("Sending frame number %d \n", frame_number);
    sleep(1);
    int rand = random() % 100;
    if (rand < LOSS_PROBABILITY)
    {
        printf("Frame %d lost during transmission \n", frame_number);
        return 0;
    }
    else
    {
        printf("Frame %d received succesfully \n", frame_number);
        return 1;
    }
}

int receive_ack(int frame_number)
{
    printf("Receiving acknowledgement for frame number %d \n", frame_number);
    sleep(1);
    int rand = random() % 100;
    if (rand < LOSS_PROBABILITY)
    {
        printf("Ack %d lost during transmission \n", frame_number);
        return 0;
    }
    else
    {
        printf("Ack %d received succesfully \n", frame_number);
        return 1;
    }
}

void selective()
{
    int sent_frames[TOTAL_FRAMES] = {0};
    int recieved_ack[TOTAL_FRAMES] = {0};
    int base = 0;

    while (base < TOTAL_FRAMES)
    {

        for (int i = 0; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
        {
            if (!sent_frames[i])
            {
                sent_frames[i] = send_frame(i);
            }
        }

        for (int i = 0; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
        {
            if (sent_frames[i] && !recieved_ack[i])
            {
                recieved_ack[i] = receive_ack(i);
            }
        }

        while (base < TOTAL_FRAMES && recieved_ack[base])
        {
            printf("Sliding window forward. frame %d fully acknowledged \n", base);
            base++;
        }
    }

    printf("All frames acked succesfully");
}

void main()
{
    srand(time(0));
    selective();
}