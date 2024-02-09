#include "philo.h"

static int	check_loop(t_obj *obj, int *i)
{
	pthread_mutex_lock(&obj->mutex);
	if (ft_now_ms()
		- obj->philos[*i].last_meal_beginning >= (unsigned long long)obj->time_die
		|| obj->total_finished == obj->num_philos)
	{
		if (obj->max_meals != -1 && obj->total_finished == obj->num_philos)
		{
			obj->is_full = 1;
			pthread_mutex_unlock(obj->philos[*i].left_fork);
			printf("Simulation finished ✨ \n");
		}
		else
		{
			obj->is_dead = 1;
			pthread_mutex_unlock(obj->philos[*i].left_fork);
			printf("%lu %d", ft_now_ms() - obj->start_time, obj->philos[*i].id);
			printf(RED);
			printf(" One philosopher died! 🪦 \n");
			printf(WHITE);
		}
		pthread_mutex_unlock(&obj->mutex);
		return (1);
	}
	if (*i + 1 == obj->num_philos)
		*i = -1;
	pthread_mutex_unlock(&obj->mutex);
	return (0);
}

/* This file contains main function & ft_philo */
static void	ft_philo(t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < obj->num_philos)
		pthread_create(&obj->philos[i].thread, NULL, routine, &obj->philos[i]);
	i = -1;
	while (++i < obj->num_philos && !check_loop(obj, &i))
		i = i + 0;
	i = -1;
	while (++i < obj->num_philos)
		pthread_join(obj->philos[i].thread, NULL);
	i = -1;
	while (++i < obj->num_philos)
		pthread_detach(obj->philos[i].thread);
	i = -1;
	while (++i < obj->num_philos)
		pthread_mutex_destroy(obj->philos[i].left_fork);
	i = -1;
	while (++i < obj->num_philos)
		pthread_mutex_destroy(obj->philos[i].right_fork);
}

int	main(int ac, char **av)
{
	t_obj	obj;

	if (ac == 5 || ac == 6)
	{
		if (is_input_valid(ac, av))
		{
			memset(&obj, 0, sizeof(t_obj));
			init(ac, av, &obj);
			ft_philo(&obj);
		}
	}
	else
		ft_puterr();
	return (0);
}
