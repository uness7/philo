#include "philo.h"

void	ft_printf_status(t_philo *philo, char *s)
{
	printf("%lu %d %s", ft_now_ms() - philo->last_meal_beginning, philo->id,
		s);
}

void	ft_puterr(void)
{
	printf("Args Not Enough!\n");
	printf("You have to specify 4 arguments and last one is optional.\n");
	printf("Please enter args in this exact order!\n");
	printf("1. Number of philosophers\n");
	printf("2. Time to die (ms)\n");
	printf("3. Time to eat (ms)\n");
	printf("4. Time to sleep (ms)\n");
	printf("5. Times a philo has to eat and then die (ms) (optional)\n");
}

uint64_t	ft_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL);
}

void	get_args(int ac, char **av, t_obj *obj)
{
	if (ac == 5)
	{
		obj->num_philos = ft_atoi(av[1]);
		obj->time_eat = ft_atoi(av[2]);
		obj->time_sleep = ft_atoi(av[3]);
		obj->time_die = ft_atoi(av[4]);
	}
	if (ac == 6)
		obj->times_eat_die = ft_atoi(av[5]);
	obj->start_time = ft_now_ms();
}
