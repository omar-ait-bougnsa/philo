#include "philosophers.h"
int i;
i = 0;
void *moniture (void *data1)
{
    t_data *data;
    data = (t_data *) data1;
    while (1)
    {
        
        if (i == data->philo - 1)
        {
            i = 0;
        }
        pthread_mutex_lock (&data->mutex);
        pthread_mutex_lock (&data->eat_lock);
        if (data->philosophers[i].eat == 1 && ft_gettime() - data->philosophers[i].time >= data->die)
        {
           data->philosophers->check_die = 1;
           printf("%ld %d died\n",ft_gettime() - data->philosophers[i].time,data->philosophers[i].indix);
           pthread_mutex_unlock(&data->eat_lock);
           pthread_mutex_unlock (&data->mutex);
           exit(1);
        }
        pthread_mutex_unlock(&data->eat_lock);
        pthread_mutex_unlock (&data->mutex);
    }
    return (NULL);
}