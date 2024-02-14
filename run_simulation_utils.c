#include "philo.h"

void	init_simulation(int ac, char **av, t_obj *obj)
{
	memset(obj, 0, sizeof(t_obj));
	init(ac, av, obj);
}

void	create_threads(t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < obj->num_philos)
		pthread_create(&obj->philos[i].thread, NULL, routine, &obj->philos[i]);
}

void	wait_for_threads_finish(t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < obj->num_philos)
		pthread_join(obj->philos[i].thread, NULL);
}

void	cleanup_mutex(t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < obj->num_philos)
		pthread_mutex_destroy(&obj->philos[i].left_fork);
}

void	check_simulation_end(t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < obj->num_philos && !check_simulation_state(obj, &i))
		i = i + 0;
}
