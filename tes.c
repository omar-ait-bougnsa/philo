#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    struct timeval start, end;

    // Start time
    gettimeofday(&start, NULL);
    while(1)
    {
    

    // Do some work or sleep
    usleep(50); // Sleep for 500 microseconds

    // End time
    gettimeofday(&end, NULL);
    usleep(50000);
    // Calculate the difference in microseconds
    long seconds = end.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    long elapsed = seconds * 1000 + microseconds / 1000;

    printf("Elapsed time: %ld microseconds\n", seconds);
    }

    return 0;
}
