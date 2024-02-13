#include "philo.h"

static void	_routine(t_philo *philo)
{
	while (1)
	{
		if (!pickup_forks(philo))
			break ;
		pthread_mutex_lock(&philo->obj->mutex);
		philo->meals++;
		philo->lmb = ft_time();
		pthread_mutex_unlock(&philo->obj->mutex);
		ft_write_status(philo, "is eating 🍝");
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
}

static void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!(philo->id & 1))
		ft_usleep(10);
	_routine(philo);
	return (NULL);
}

static bool	check_loop(t_obj *obj, int *i)
{
	pthread_mutex_lock(&obj->mutex);
	if (ft_time() - obj->philos[*i].lmb >= (unsigned long long)obj->time_die \
			|| obj->total_finished == obj->num_philos)
	{
		printf(RED);
		if (obj->max_meals != -1 && obj->total_finished == obj->num_philos)
		{
			obj->is_full = true;
			pthread_mutex_unlock(&obj->philos[*i].left_fork);
			printf("Simulation finished ✨ \n");
		}
		else
		{
			obj->is_dead = true;
			pthread_mutex_unlock(&obj->philos[*i].left_fork);
			printf("%lu %d died 🪦\n", ft_time() - obj->st, obj->philos[*i].id);
		}
		printf(WHITE);
		pthread_mutex_unlock(&obj->mutex);
		return (true);
	}
	if (*i + 1 == obj->num_philos)
		*i = -1;
	pthread_mutex_unlock(&obj->mutex);
	return (false);
}

static void	ft_philo(int ac, char **av)
{
	int		i;
	t_obj	obj;

	memset(&obj, 0, sizeof(t_obj));
	init(ac, av, &obj);
	i = -1;
	while (++i < obj.num_philos)
		pthread_create(&obj.philos[i].thread, NULL, routine, &obj.philos[i]);
	i = -1;
	while (++i < obj.num_philos && !check_loop(&obj, &i))
		i = i + 0;
	i = -1;
	while (++i < obj.num_philos)
		pthread_join(obj.philos[i].thread, NULL);
	i = -1;
	while (++i < obj.num_philos)
		pthread_mutex_destroy(&obj.philos[i].left_fork);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (is_input_valid(ac, av))
			ft_philo(ac, av);
	}
	else
		ft_puterr();
	return (0);
}
