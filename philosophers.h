#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#endif

struct data;

typedef struct t_philo
{
    int time_eat;
    int time_die;
    int time_sleep;
    pthread_t id;
    int indix;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long time;
    long time3;
    int check_die;
    int eat;
    struct timeval time1;
    struct timeval time2;
    int time_to_eat;
    long tm;
    struct data  *data;
} t_philo;

typedef struct data
{
    pthread_mutex_t *forks;
    int eat;
    int sleep;
    int philo;
    int die;
    int cheak_die;
    int time_to_eat;
    long time;
    long start_time;
    int ready;
    t_philo *philosophers;
    pthread_mutex_t mutex;
    pthread_mutex_t eat_lock;
    pthread_mutex_t mutex_time;
} t_data;
void *moniture (void *data1);