/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:08:46 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/15 15:43:04 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_routine(t_philo *philo)
{
	while (1)
	{
		if (pickup_forks(philo) == false)
		{
			break ;
		}
		increment_meals_update_lmb(philo);
		print_status(philo, "is eating 🍝");
		ft_usleep(philo->obj->time_eat);
		update_meals_count(philo);
		release_forks(philo);
		if (sleep_think(philo) == false)
		{
			break ;
		}
	}
}

/* Delay for even philosophers number to avoid simultaneous actions */
/* This is needed in create_threads function */
void	*routine(void *data)
{
	t_philo	*philo;
	bool	is_even;

	philo = (t_philo *)data;
	is_even = philo->id % 2;
	if (is_even == true)
	{
		ft_usleep(10);
	}
	philo_routine(philo);
	return (NULL);
}

void	run_simulation(int ac, char **av)
{
	t_obj	obj;

	init_simulation(ac, av, &obj);
	create_threads(&obj);
	check_simulation_end(&obj);
	wait_for_threads_finish(&obj);
	cleanup_mutex(&obj);
}
