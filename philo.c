#include "philosophers.h"

typedef struct t_philo
{
    int time_eat;
    int time_die;
    int time_sleep;
    pthread_t id;
    int indix;
    pthread_mutex_t *fork1;
    pthread_mutex_t *fork2;
    long time;
    long time3;
    int check_die;
    int eat;
    struct timeval time1;
    struct timeval time2;
    int time_to_eat;
    long tm;
} t_philo;

int ft_atoi(char *str)
{
    int i;
    i = 0;
    int nbr;
    nbr = 0;
    int a;
    a = 1;
    while(str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            a = -a;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        nbr = nbr * 10 + str[i] - '0';
        i++;
    }
    return(nbr * a);
}

void check_philo(char **av ,t_data *data)
{
    data->philo = ft_atoi(av[1]);
    data->die = ft_atoi(av[2]);
    data->eat = ft_atoi(av[3]);
    data->sleep = ft_atoi(av[4]);
    data->time_to_eat = 0;
    if (av[5] != NULL)
        {
            data->time_to_eat = ft_atoi(av[5]);
            if (data->time_to_eat == 0)
            {
                printf ("invalid argument \n");
                exit (1);
            }
        }
    if (data->philo <= 0 || data->die <= 0 || data->eat <= 0 || data->sleep <= 0)
    {
        printf ("invalid argument \n");
        exit (1);
    }
}
long  ft_gettime()
{
    long tm;
    struct timeval time;
    gettimeofday(&time,NULL);
    tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return(tm);
}
void  taken_afork(t_philo *philo)
{
    pthread_mutex_lock(philo->fork1);
    philo->tm = ft_gettime();
    printf ("%ld %d has taken a fork\n",philo->tm - philo->time3,philo->indix);
    pthread_mutex_lock(philo->fork2);
     philo->tm = ft_gettime();
    printf ("%ld %d has taken a fork\n",philo->tm - philo->time3, philo->indix);
    philo->time = ft_gettime();
    printf ("\033[31m%ld %d is eating\n\033[0m",philo->tm - philo->time3, philo->indix);
    philo->time_eat++;
    usleep(philo->time_eat * 1000); 
    philo->time = ft_gettime();
    philo->eat = 1;
    pthread_mutex_unlock(philo->fork1);
    pthread_mutex_unlock(philo->fork2); 
}

void *ft_rotine(void *data)
{
    t_philo *philo;
    philo = (t_philo*)data;
     if (philo->indix % 2 == 1)
            usleep(20);
    philo->time3 = ft_gettime();
    while (1)
    {
        if (philo->check_die == 1)
            break;
        taken_afork(philo);
        philo->tm = ft_gettime();
        printf ("%ld %d is sleeping\n",philo->tm - philo->time3, philo->indix);
        usleep(philo->time_sleep * 1000);
        philo->tm = ft_gettime();
        printf ("%ld %d is thinking\n",philo->tm - philo->time3, philo->indix);
    }
    return (NULL);
}

void creat_pthread(t_philo *philo,t_data *data)
{
    int i;
    i = 0;
    while (i < data->philo)
    {
        memset(&philo[i],0,sizeof(t_philo));
        philo[i].time_eat = data->eat;
        philo[i].time_sleep = data->sleep;
        philo[i].time_die = data->die;
        philo[i].fork1 = &data->forks[i];
        philo[i].check_die = 0;
        philo[i].check_die = 0;
        if (i == data->philo - 1)
            philo[i].fork2 = &data->forks[0];
        else 
            philo[i].fork2 = &data->forks[i + 1];
        philo[i].indix = i;
        pthread_create(&philo[i].id,NULL,ft_rotine,&philo[i]);
        i++;
    }
}

void creat_metex(t_data *data)
{
    int i ;
    i = 0;
    while (i < data->philo)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        i++;
    }
}
int main(int ac, char **av)
{
    t_data data;
    t_philo *philo;
    if (ac != 5 &&  ac != 6)
    {
        printf ("pleas 4 or 5 argument\n");
        return (0);
    }
    check_philo(av ,&data);
    philo = malloc (data.philo * sizeof(t_philo));
    data.forks = malloc (data.philo * sizeof(pthread_mutex_t));
    creat_metex(&data);
    creat_pthread(philo,&data);
    int i = 0;
    while (1)
    {
        if (i == data.philo - 1)
        {
            i = 0;
        }
        data.time = ft_gettime();
       // printf(" new time %ld\n",data.time);
      //printf("lest time to eat %ld\n",data.time - philo[i].time);
        if (philo[i].eat == 1 && data.time - philo[i].time >= data.die)
        {
           philo->check_die = 1;
           printf("%ld %d died\n",data.time - philo[i].time3,philo[i].indix);
           usleep(20);
           return(0);
        }
        if (data.time_to_eat != 0)
        {
            if (philo[1].time_to_eat >= data.time_to_eat)
                exit(1);
        }
        i++;
    }
    return 0;

}
