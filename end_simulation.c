/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:09:54 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/19 11:23:31 by yzioual          ###   ########.fr       */
/*   Updated: 2024/02/16 16:47:13 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_death_or_finish(t_obj *obj, int *i)
{
	bool				first_cond;
	bool				second_cond;
	unsigned long long	time_die_ull;

	time_die_ull = (unsigned long long)obj->time_die;
	pthread_mutex_lock(&obj->mutex);
	first_cond = ft_time() - obj->philos[*i].lmb >= time_die_ull;
	second_cond = obj->num_philos_finished_max_meals == obj->num_philos;
	pthread_mutex_unlock(&obj->mutex);
	if (first_cond == true || second_cond == true)
<<<<<<< HEAD
		return (true);
=======
	{
		return (true);
	}
>>>>>>> 25f4525 (commit got rid of forks array)
	return (false);
}

static bool	handle_simulation_end(t_obj *obj, int *i)
{
	pthread_mutex_lock(&obj->mutex);
	if (obj->max_meals != -1
		&& obj->num_philos_finished_max_meals == obj->num_philos)
	{
		obj->is_full = true;
		printf("Simulation finished ✨ \n");
	}
	else
	{
		obj->is_dead = true;
		printf("%lu %d died 🪦\n", ft_time() - obj->st, obj->philos[*i].id);
	}
	pthread_mutex_unlock(&obj->mutex);
	return (true);
}

bool	check_philosopher_state(t_obj *obj, int *i)
{
	bool	reset;

	if (check_death_or_finish(obj, i) == true)
	{
		return (handle_simulation_end(obj, i));
	}
	reset = obj->num_philos == *i + 1;
	if (reset == true)
	{
		*i = -1;
	}
	return (false);
}
