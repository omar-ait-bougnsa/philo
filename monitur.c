#include "philosophers.h"

void	tf_moniture(t_data *data)
{
	int i;
	i = 0;
	if (data->philo == 1)
	{
		pthread_join(data->philosophers[0].id, NULL);
		ft_sleep(data->die);
		print_status(data->philosophers, "died");
		return ;
	}
	while (1)
	{
		i = 0;
		if (i < data->philo )
		{

		//pthread_mutex_lock(&data->mutex);
		pthread_mutex_lock(&data->eat_lock);
		// if (data->philosophers[i].time % 2 == 1)
		// {
		// 	data->philosophers[i].time = data->philosophers[i].time - 800 / 1000;
		// }
		if (data->philosophers[i].eat == 1 && ft_gettime() - data->philosophers[i].time >= data->die)
		{
			pthread_mutex_lock(&data->mutex);
			data->cheak_die = 1;
			pthread_mutex_unlock(&data->mutex);
			printf("%ld %d died\n", ft_gettime() - data->start_time,data->philosophers[i].indix);
			pthread_mutex_unlock(&data->eat_lock);
			return ;
		}
		pthread_mutex_unlock(&data->eat_lock);
		i++;
		}
		//pthread_mutex_unlock(&data->mutex);
		// pthread_mutex_lock(&data->eat_lock);
		// if (data->time_to_eat != 0)
		// {
		// 	if (data->philosophers[1].time_to_eat >= data->time_to_eat)
		// 		exit(1);
		// }
		// pthread_mutex_unlock(&data->eat_lock);
		//i++;
	}
}