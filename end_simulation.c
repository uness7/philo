#include "philo.h"

static bool	check_death_or_finish(t_obj *obj, int *i)
{
	unsigned long long	time_die_ull;
	bool				first_cond;

	pthread_mutex_lock(&obj->mutex);
	time_die_ull = (unsigned long long)obj->time_die;
	if (ft_time() - obj->philos[*i].lmb >= time_die_ull
		|| obj->total_finished == obj->num_philos)
	{
		pthread_mutex_unlock(&obj->mutex);
		return (true);
	}
	pthread_mutex_unlock(&obj->mutex);
	return (false);
}

static void	handle_simulation_end(t_obj *obj, int *i)
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
}

bool	check_simulation_state(t_obj *obj, int *i)
{
	if (check_death_or_finish(obj, i))
	{
		handle_simulation_end(obj, i);
		return (true);
	}
	if (*i + 1 == obj->num_philos)
		*i = -1;
	return (false);
}
