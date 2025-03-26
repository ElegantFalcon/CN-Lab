#include <stdio.h>
#include <stdlib.h>

void leaky_bucket(int bucket_capacity, int leak_rate, int num_packets, int packets[])
{
    int bucket = 0;

    printf("Time \t Incoming \t Bucket \t Leaked \t Remaining \n");
    for (int i = 0; i < num_packets; i++)
    {
        printf("%d%10d", i + 1, packets[i]);

        bucket += packets[i];

        if (bucket > bucket_capacity)
        {
            printf(" Overflow,Dropped ");
            bucket = bucket_capacity;
        }
        else
        {
            printf("%10d",bucket);
        }

        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        bucket -= leaked;

        printf("%10d%10d \n", leaked, bucket);
    }

    int time = num_packets + 1;
    while (bucket > 0)
    {
        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        printf("%d%10d%10d%10d%10d\n",time,0,bucket,leaked,bucket-leaked);
        bucket -= leaked;
        time++;
    }
}

void main()
{
    int packets[5] = {6, 4, 2, 8, 3};
    leaky_bucket(10, 3, 5, packets);
}