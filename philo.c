#include "philosophers.h"

long	ft_gettime(void)
{
	long			tm;
	struct timeval	time;

	gettimeofday(&time, NULL);
	tm = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (tm);
}

int	print_status(t_philo *philo, char *status)
{
	
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->cheak_die == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (0) ;
	}
	printf("%ld %d %s\n", ft_gettime() - philo->data->start_time, philo->indix,status);
	pthread_mutex_unlock(&philo->data->mutex);
	return (1);
}
void	ft_sleep(long time)
{
	long	start;

	start = ft_gettime();
	while (ft_gettime() - start < time)
		;
}

void	*routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	print_status(philo, "has taken a fork");
	return (NULL);
}

void	creat_pthread(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->ready = 0;
	data->start_time = ft_gettime();
	while (i < data->philo)
	{
		philo[i].time_eat = data->eat;
		philo[i].time_sleep = data->sleep;
		philo[i].time_to_eat = 0;
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

void	creat_metex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->mutex_time, NULL);
	pthread_mutex_init(&data->mutex_time1, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	while (i < data->philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	start_routine(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ft_gettime();
	if (data->philo == 1)
	{
		pthread_create(&data->philosophers[0].id, NULL, routine_philo,
			&data->philosophers[0]);
		return (0);
	}
	while (++i < data->philo)
		pthread_create(&data->philosophers[i].id, NULL, ft_rotine,
			&data->philosophers[i]);
	pthread_mutex_lock(&data->mutex);
	data->ready = 1;
	pthread_mutex_unlock(&data->mutex);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	data.cheak_die = 0;
	data.nbr_to_eat = 0;
	if (ac != 5 && ac != 6)
	{
		printf("pleas 4 or 5 argument\n");
		return (0);
	}
	check_philo(av, &data);
	data.philosophers = malloc(data.philo * sizeof(t_philo));
	data.forks = malloc(data.philo * sizeof(pthread_mutex_t));
	creat_metex(&data);
	creat_pthread(data.philosophers, &data);
	start_routine(&data);
	//i = 0;
	tf_moniture(&data);
	i = -1;
	while(++i < data.philo)
	    pthread_join(data.philosophers[i].id, NULL);
	return (0);
}
