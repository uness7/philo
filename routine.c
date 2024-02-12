#include "philo.h"

bool	ft_write_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->obj->mutex);
	if (philo->obj->is_dead || philo->obj->is_full)
	{
		pthread_mutex_unlock(&philo->obj->mutex);
		return (false);
	}
	printf("%lu %d %s\n", ft_now_ms() - philo->obj->start_time, philo->id,
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
	printf(YELLOW);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (false);
	}
	if (ft_should_stop(philo))
		return (false);
	pthread_mutex_lock(philo->right_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	printf(WHITE);
	return (true);
}

bool	ft_sleep_think(t_philo *philo)
{
	if (!ft_write_status(philo, "is sleeping"))
		return (false);
	ft_usleep(philo->obj->time_sleep);
	if (!ft_write_status(philo, "is thinking"))
		return (false);
	return (true);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!(philo->id & 1))
		ft_usleep(10);
	while (1)
	{
		if (!pickup_forks(philo))
			break ;

		pthread_mutex_lock(&philo->obj->mutex);
		philo->meals++;
		philo->last_meal_beginning = ft_now_ms();
		pthread_mutex_unlock(&philo->obj->mutex);

		ft_write_status(philo, "is eating");
		ft_usleep(philo->obj->time_eat);
		pthread_mutex_lock(&philo->obj->mutex);
		if (philo->meals == philo->obj->max_meals)
			philo->obj->total_finished += (philo->obj->max_meals != -1);
		pthread_mutex_unlock(&philo->obj->mutex);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (!ft_sleep_think(philo))
			break ;
	}
	return (NULL);
}
