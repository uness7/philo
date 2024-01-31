#include "philo.h"

void	think(t_philo *philo)
{
	philo->is_thinking = 1;
	printf("Philosopher %d is thinking\n", philo->id);
	usleep(10000);
}

void	eat(t_philo *philo)
{
	philo->is_eating = 1;
	printf("Philosopher %d is eating\n", philo->id);
	usleep(philo->time_eat);
}

void	ft_sleep(t_philo *philo)
{
	philo->is_sleeping = 1;	
	printf("Philosopher %d is sleeping\n", philo->id);
	usleep(philo->time_sleep);
}

int	is_input_valid(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + (s[i++] - '0');
	return (result);
}
