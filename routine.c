#include "philo.h"

bool	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->obj->mutex);
	if (philo->obj->is_dead || philo->obj->is_full)
	{
		pthread_mutex_unlock(&philo->obj->mutex);
		return (false);
	}
	printf("%lu %d %s\n", ft_time() - philo->obj->st, philo->id,
		msg);
	pthread_mutex_unlock(&philo->obj->mutex);
	return (true);
}

bool	check_state(t_philo *philo)
{
	bool	return_value;

	pthread_mutex_lock(&philo->obj->mutex);
	return_value = philo->obj->is_dead || philo->obj->is_full;
	pthread_mutex_unlock(&philo->obj->mutex);
	return (return_value);
}

bool	pickup_forks(t_philo *philo)
{
	if (check_state(philo))
		return (false);
	pthread_mutex_lock(&philo->left_fork);
	if (!print_status(philo, "has taken a fork 🍴"))
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (false);
	}
	if (check_state(philo))
		return (false);
	pthread_mutex_lock(philo->right_fork);
	if (!print_status(philo, "has taken a fork 🍴"))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

bool	sleep_think(t_philo *philo)
{
	printf(BLUE);
	if (!print_status(philo, "is sleeping 💤"))
		return (false);
	printf(WHITE);
	ft_usleep(philo->obj->time_sleep);
	printf(YELLOW);
	if (!print_status(philo, "is thinking 💭"))
		return (false);
	printf(WHITE);
	return (true);
}
