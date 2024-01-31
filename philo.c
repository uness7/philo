#include "philo.h"
#include <sys/time.h>

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pickup_forks(philo);
		eat(philo);
		putdown_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
}

static void	ft_philo(t_obj obj)
{
	pthread_t		philos_threads[obj.num_philos];
	pthread_mutex_t	forks[obj.num_philos];
	t_philo			philo[obj.num_philos];
	int				i;

	i = 0;
	while (i < obj.num_philos)
	{
		philo[i].time_sleep = obj.time_sleep;
		philo[i].time_eat = obj.time_eat;
		philo[i].time_die = obj.time_die;
		i++;
	}
	while (1)
	{
		i = -1;
		while (++i < obj.num_philos)
		{
			philo[i].id = i;
			philo[i].left_fork = &forks[i];
			philo[i].right_fork = &forks[(i + 1) % obj.num_philos];
			pthread_mutex_init(&forks[i], NULL);
			pthread_create(&philos_threads[i], NULL, &routine, &philo[i]);
		}
		i = -1;
		while (++i < obj.num_philos)
			pthread_join(philos_threads[i], NULL);
	}
}

int	main(int ac, char **av)
{
	t_obj	obj;

	if (ac == 5 || ac == 6)
	{
		if (is_input_valid(ac, av))
		{
			obj.num_philos = ft_atoi(av[1]);
			obj.time_eat = ft_atoi(av[2]);
			obj.time_sleep = ft_atoi(av[3]);
			obj.time_die = ft_atoi(av[4]);
			if (ac == 6)
				obj.times_eat_die = ft_atoi(av[5]);
			ft_philo(obj);
		}
	}
	else
		ft_puterr();
	return (0);
}
