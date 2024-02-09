#include "philo.h"

/* We have to initialize two structures : philo & obj */
static void	init_obj(int ac, char **av, t_obj *obj)
{
	obj->num_philos = ft_atoi(av[1]);	
	if (obj->num_philos > 200)
		ft_puterr();
	obj->time_die = ft_atoi(av[2]);
	obj->time_eat = ft_atoi(av[3]);
	obj->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		obj->max_meals = ft_atoi(av[5]);
		if (obj->max_meals == 0)
			ft_puterr();
	}
	pthread_mutex_init(&obj->mutex, NULL);
	obj->start_time = ft_now_ms();
}

static void	init_philo(t_obj *obj)
{
	pthread_mutex_t		forks[obj->num_philos];
	int	i;

	i = -1;
	while (++i < obj->num_philos)
	{
		obj->philos[i].id = i;
		obj->philos[i].last_meal_beginning = obj->start_time;
		pthread_mutex_init(&forks[i], NULL);
		obj->philos[i].left_fork = &forks[i];
		obj->philos[i].right_fork = &forks[(i + 1) % obj->num_philos];
		obj->philos[i].obj = obj;
	}	
}

void	init(int ac, char **av, t_obj *obj)
{
	init_obj(ac, av, obj);	
	init_philo(obj);
}
