#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		printf("Error trying to pickup left_fork!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf(YELLOW);
		ft_printf_status(philo, "has taken a fork 🍽️\n");
		printf(WHITE);
	}
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		printf("Error trying to pickup right fork!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf(YELLOW);
		ft_printf_status(philo, "has taken a fork 🍽️ \n");
		printf(WHITE);
	}
}

void	putdown_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		exit(EXIT_FAILURE);
}
