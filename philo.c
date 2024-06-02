#include "philosophers.h"

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

long  ft_gettime1()
{
    long tm;
    struct timeval time;
    gettimeofday(&time,NULL);
    tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return(tm);
}
void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->mutex);
    if (philo->data->cheak_die == 1)
    {
         pthread_mutex_unlock(&philo->data->mutex);
            return;
    }
    printf ("%ld %d %s\n", ft_gettime() - philo->data->start_time, philo->indix, status);
    pthread_mutex_unlock(&philo->data->mutex);
}
void ft_sleep(long time)
{
    long start = ft_gettime();
    while(ft_gettime() - start < time);
}

void  taken_afork(t_philo *philo)
{
    if (philo->indix % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork1");
        pthread_mutex_lock(philo->left_fork); 
        print_status(philo, "has taken a fork2");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork1");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork2");
    }
    pthread_mutex_lock(&philo->data->eat_lock);
    philo->time = ft_gettime(); 
    philo->eat = 1;
    pthread_mutex_unlock(&philo->data->eat_lock);
    print_status(philo, "is eating");
    ft_sleep(philo->time_eat); 
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork); 
}


void *ft_rotine(void *data)
{
    t_philo *philo;
    philo = (t_philo*)data;
    if (philo->indix % 2 == 1)
            usleep(200);
    while (1)
    {
        taken_afork(philo);
        print_status(philo, "is sleeping");
        ft_sleep(philo->time_sleep);
        print_status(philo, "is thinking");
    }
    return (NULL);
}
void *routine_philo(void *data)
{
    t_philo *philo;
    philo = (t_philo*)data;
    print_status(philo,"has taken a fork");
    return (NULL);
}

void creat_pthread(t_philo *philo,t_data *data)
{
    int i;
    i = 0;
    data->ready = 0;
    data->start_time = ft_gettime();
    while (i < data->philo)
    {
        philo[i].time_eat = data->eat;
        philo[i].time_sleep = data->sleep;
        // if (philo[i].indix % 2)
        // {
             philo[i].left_fork = &data->forks[i];
            philo[i].right_fork = &data->forks[(i + 1) % data->philo];
        // }
        // else 
        // {
        //      philo[i].right_fork = &data->forks[i];
        //     philo[i].left_fork = &data->forks[(i + 1) % data->philo];
        //  }
        philo[i].indix = i + 1;
        philo[i].data = data;
        // pthread_create(&philo[i].id,NULL,ft_rotine,&philo[i]);
        i++;
    }
}

void creat_metex(t_data *data)
{
    int i ;
    i = 0;
    pthread_mutex_init(&data->mutex, NULL);
    pthread_mutex_init(&data->mutex_time, NULL);
    pthread_mutex_init(&data->eat_lock, NULL);
    while (i < data->philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}

int start_routine(t_data *data)
{
    int i = -1;
    data->start_time = ft_gettime();
     if (data->philo == 1)
    {
        pthread_create(&data->philosophers[0].id,NULL,routine_philo,&data->philosophers[0]); 
        return (0);
    }
    while(++i < data->philo)
        pthread_create(&data->philosophers[i].id, NULL, ft_rotine, &data->philosophers[i]);
    pthread_mutex_lock(&data->mutex);
    data->ready = 1;
    pthread_mutex_unlock(&data->mutex);
    return 0;
}

int main(int ac, char **av)
{
    t_data data;
    data.cheak_die = 0;
    if (ac != 5 &&  ac != 6)
    {
        printf ("pleas 4 or 5 argument\n");
        return (0);
    }
    check_philo(av ,&data);
    data.philosophers = malloc (data.philo * sizeof(t_philo));
    data.forks = malloc (data.philo * sizeof(pthread_mutex_t));
    creat_metex(&data);
    creat_pthread(data.philosophers, &data);
    start_routine(&data);
    int i = 0;
    if (data.philo == 1)
    {
        pthread_join(data.philosophers[0].id, NULL);
        ft_sleep(data.die);
        print_status(data.philosophers,"died");
        return (0);
    }
    while (1)
    {
        
        if (i == data.philo - 1)
        {
            i = 0;
        }
        pthread_mutex_lock (&data.mutex);
        pthread_mutex_lock (&data.eat_lock);
        if (data.philosophers[i].eat == 1 && ft_gettime() - data.philosophers[i].time >= data.die)
        {
          data.cheak_die = 1;
           printf("%ld %d died\n",ft_gettime() - data.start_time,data.philosophers[i].indix);
           pthread_mutex_unlock(&data.eat_lock);
           pthread_mutex_unlock (&data.mutex);
           exit(1);
        }
        pthread_mutex_unlock(&data.eat_lock);
        pthread_mutex_unlock (&data.mutex);
        // if (data.time_to_eat != 0)
        // {
        //     if (philo[1].time_to_eat >= data.time_to_eat)
        //         exit(1);
        // }
        i++;
    }
    // i = -1;
    // while(++i < data.philo)
    //     pthread_join(data.philosophers[i].id, NULL);

    return 0;
}
