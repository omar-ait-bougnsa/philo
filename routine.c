#include "philosophers.h"

void	taken_afork(t_philo *philo)
{
	if (philo->indix % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_status(philo, "has taken a fork") == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			return;
		}
		pthread_mutex_lock(philo->right_fork);
		if (print_status(philo, "has taken a fork") == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return;
		}
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (print_status(philo, "has taken a fork") == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			return;
		}
		pthread_mutex_lock(philo->left_fork);
		if (print_status(philo, "has taken a fork") == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return;
		}
	}
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->time = ft_gettime();
	philo->eat = 1;
	philo->data->nbr_to_eat++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	if (print_status(philo, "is eating") == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	ft_sleep(philo->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_rotine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->time = ft_gettime();
	philo->eat = 1;
	pthread_mutex_unlock(&philo->data->eat_lock);
	while (1)
	{
		if (philo->indix % 2 == 1)
			usleep(700);
		taken_afork(philo);
		if (print_status(philo, "is sleeping") == 0)
			return(NULL);
		ft_sleep(philo->time_sleep);
        pthread_mutex_lock(&philo->data->mutex_time1);
		if (print_status(philo, "is thinking") == 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_time1);
			return (NULL);
		}
        pthread_mutex_unlock(&philo->data->mutex_time1);
	}
	return (NULL);
}