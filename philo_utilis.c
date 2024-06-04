#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nbr;
	int	a;

	i = 0;
	nbr = 0;
	a = 1;
	while (str[i] == ' ' || str[i] == '\t')
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
	return (nbr * a);
}
void	check_philo(char **av, t_data *data)
{
	data->time_to_eat = 0;
	data->philo = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	data->time_to_eat = 0;
	if (av[5] != NULL)
	{
		data->time_to_eat = ft_atoi(av[5]);
		if (data->time_to_eat <= 0)
		{
			printf("invalid argument \n");
			exit(1);
		}
	}
	if (data->philo <= 0 || data->die <= 0 || data->eat <= 0
		|| data->sleep <= 0)
	{
		printf("invalid argument \n");
		exit(1);
	}
}
