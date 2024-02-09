#include "philo.h"

void	ft_usleep(uint64_t milli)
{
	uint64_t	now;
	uint64_t	elapsed;

	now = ft_now_ms();
	elapsed = ft_now_ms();
	while (elapsed - now < milli)
	{
		usleep(333);
		elapsed = ft_now_ms();
	}
}

int	ft_write_status(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->obj->mutex);
	if (philo->obj->is_dead || philo->obj->is_full)
	{
		pthread_mutex_unlock(&philo->obj->mutex);
		return (0);
	}
	printf("%lu %d %s\n", ft_now_ms() - philo->obj->start_time, philo->id,
		message);
	pthread_mutex_unlock(&philo->obj->mutex);
	return (1);
}

int	ft_should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->obj->mutex);
	if (philo->obj->is_dead || philo->obj->is_full)
	{
		pthread_mutex_unlock(&philo->obj->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->obj->mutex);
	return (0);
}

int	pickup_forks(t_philo *philo)
{
	if (ft_should_stop(philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	printf(YELLOW);
	if (!ft_write_status(philo, "has taken a fork  🍽️"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	printf(WHITE);
	if (ft_should_stop(philo))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	printf(YELLOW);
	if (!ft_write_status(philo, "has taken a fork  🍽️"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	printf(WHITE);
	return (1);
}

int	ft_think(t_philo *philo)
{
	if (!ft_write_status(philo, "is thinking 💭 "))
		return (0);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	printf(BLUE);
	if (!ft_write_status(philo, "is sleeping 💤 "))
		return (0);
	printf(WHITE);
	ft_usleep(philo->obj->time_sleep);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
		printf(GREEN);
		ft_write_status(philo, "is eating 🍝");
		printf(WHITE);
		ft_usleep(philo->obj->time_eat);
		pthread_mutex_lock(&philo->obj->mutex);
		if (philo->meals == philo->obj->max_meals)
			philo->obj->total_finished += (philo->obj->max_meals != -1);
		pthread_mutex_unlock(&philo->obj->mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (!ft_sleep(philo) || !ft_think(philo))
			break ;
	}
	return (NULL);
}
