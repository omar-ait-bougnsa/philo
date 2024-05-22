#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <pthread.h>
#endif

typedef struct data
{
    pthread_mutex_t *forks;
    int eat;
    int sleep;
    int philo;
    int die;
} t_data;