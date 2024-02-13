#include "philo.h"

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
	obj->st = ft_time();
}

static void	init_philo(t_obj *obj)
{
	pthread_mutex_t	forks[obj->num_philos];
	int				i;

	i = -1;
	while (++i < obj->num_philos)
	{
		obj->philos[i].id = i + 1;
		obj->philos[i].lmb = obj->st;
		pthread_mutex_init(&forks[i], NULL);
		if (i + 1 == obj->num_philos)
			obj->philos[i].right_fork = &obj->philos[0].left_fork;
		else
			obj->philos[i].right_fork = &obj->philos[i + 1].left_fork;
		obj->philos[i].obj = obj;
	}
}

void	init(int ac, char **av, t_obj *obj)
{
	init_obj(ac, av, obj);
	init_philo(obj);
}
