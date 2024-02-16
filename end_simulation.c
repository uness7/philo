/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:09:54 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/15 12:55:57 by yzioual          ###   ########.fr       */
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
	if (first_cond || second_cond)
	{
		pthread_mutex_unlock(&obj->mutex);
		return (true);
	}
	pthread_mutex_unlock(&obj->mutex);
	return (false);
}

static void	handle_simulation_end(t_obj *obj, int *i)
{
	if (obj->max_meals != -1
		&& obj->num_philos_finished_max_meals == obj->num_philos)
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
}

bool	check_philosopher_state(t_obj *obj, int *i)
{
	bool	reset;

	if (check_death_or_finish(obj, i) == true)
	{
		handle_simulation_end(obj, i);
		return (true);
	}
	reset = obj->num_philos == *i + 1;
	if (reset == true)
		*i = -1;
	return (false);
}
