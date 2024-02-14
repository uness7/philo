#include "philo.h"

bool	ft_write_status(t_philo *philo, char *msg)
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

bool	ft_should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->obj->mutex);
	if (philo->obj->is_dead || philo->obj->is_full)
	{
		pthread_mutex_unlock(&philo->obj->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->obj->mutex);
	return (false);
}

bool	pickup_forks(t_philo *philo)
{
	if (ft_should_stop(philo))
		return (false);
	pthread_mutex_lock(&philo->left_fork);
	if (!ft_write_status(philo, "has taken a fork 🍴"))
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (false);
	}
	if (ft_should_stop(philo))
		return (false);
	pthread_mutex_lock(philo->right_fork);
	if (!ft_write_status(philo, "has taken a fork 🍴"))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

bool	ft_sleep_think(t_philo *philo)
{
	printf(BLUE);
	if (!ft_write_status(philo, "is sleeping 💤"))
		return (false);
	printf(WHITE);
	ft_usleep(philo->obj->time_sleep);
	printf(YELLOW);
	if (!ft_write_status(philo, "is thinking 💭"))
		return (false);
	printf(WHITE);
	return (true);
}
