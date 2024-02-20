/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:08:46 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/19 11:38:02 by yzioual          ###   ########.fr       */
/*   Updated: 2024/02/16 16:18:50 by yzioual          ###   ########.fr       */
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
		print_status(philo, "is eating");
		ft_usleep(philo->obj->time_eat);
		update_meals_count(philo);
		release_forks(philo);
		if (sleep_think(philo) == false)
		{
			break ;
		}
	}
}

void	*routine(void *data)
{
	bool	is_even;
	t_philo	*philo;

	philo = (t_philo *)data;
	is_even = philo->id % 2;
	if (is_even == true)
	{
		ft_usleep(10);
	}
	philo_routine(philo);
	return (NULL);
}

<<<<<<< HEAD
static void	detach_threads(t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < obj->num_philos)
		pthread_detach(obj->philos[i].thread);
=======
void	*monitor_routine(void *data)
{
	t_obj	*obj;
	int	i;

	obj = (t_obj *)data;
	while (true)
	{
		i = 0;
		while (i < obj->num_philos)
		{
			pthread_mutex_lock(&obj->mutex);
			if (obj->is_dead == true)
				exit(EXIT_SUCCESS);
			pthread_mutex_unlock(&obj->mutex);
			i++;
		}
		usleep(10000); 
	}
	return (NULL);
>>>>>>> 25f4525 (commit got rid of forks array)
}

void	run_simulation(int ac, char **av)
{
	pthread_t	monitor;
	t_obj		obj;

	init_simulation(ac, av, &obj);
	create_threads(&obj);
	pthread_create(&monitor, NULL, monitor_routine, &obj);
	check_simulation_end(&obj);
	detach_threads(&obj);
	wait_for_threads_finish(&obj);
	cleanup_mutex(&obj);
}
