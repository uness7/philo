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

void	*timer_routine(void *arg)
{
	double	elapsed_time;
	t_philo	*philo;
	struct timeval start_time;
	struct timeval current_time;

	philo = (t_philo *)arg;
	gettimeofday(&start_time, NULL);
	while (!philo->has_eaten)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec)
			+ (current_time.tv_usec - start_time.tv_usec) / 1000000.0;
		if (elapsed_time > philo->time_die)
		{
			philo->has_eaten = 1;
			ft_printf_status(philo, "died!\n");
			exit(EXIT_FAILURE);
			return (NULL);
		}
	}
	return (NULL);
}

static void	ft_philo(t_obj *obj)
{
	pthread_t		timer_threads[obj->num_philos];
	pthread_t		philos_threads[obj->num_philos];
	pthread_mutex_t		forks[obj->num_philos];
	t_philo			philo[obj->num_philos];
	int				i;

	i = 0;
	while (i < obj->num_philos)
	{
		philo[i].time_sleep = obj->time_sleep;
		philo[i].time_eat = obj->time_eat;
		philo[i].time_die = obj->time_die;
		philo[i].has_eaten = 0;
		philo[i].last_meal_beginning = obj->start_time;
		philo[i].meals_max = obj->meals_max;
		i++;
	}
	while (1)
	{
		i = -1;
		while (++i < obj->num_philos)
		{
			philo[i].id = i;
			philo[i].left_fork = &forks[i];
			philo[i].right_fork = &forks[(i + 1) % obj->num_philos];
			pthread_mutex_init(&forks[i], NULL);
			pthread_create(&philos_threads[i], NULL, &routine, &philo[i]);
			pthread_create(&timer_threads[i], NULL, &timer_routine, &philo[i]);
		}
		i = -1;
		while (++i < obj->num_philos)
		{
			pthread_join(philos_threads[i], NULL);
			pthread_join(timer_threads[i], NULL);
		}
		i = -1;
		while (++i < obj->num_philos)
			pthread_detach(philos_threads[i]);
		i = -1;
		while (++i < obj->num_philos)
			pthread_mutex_destroy(&forks[i]);
	}
}

int	main(int ac, char **av)
{
	t_obj	obj;

	if (ac == 5 || ac == 6)
	{
		if (is_input_valid(ac, av))
		{
			get_args(ac, av, &obj);
			ft_philo(&obj);
		}
	}
	else
		ft_puterr();
	return (0);
}
