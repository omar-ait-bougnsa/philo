#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#endif

typedef struct data
{
    pthread_mutex_t *forks;
    int eat;
    int sleep;
    int philo;
    int die;
    struct timeval time;
} t_data;