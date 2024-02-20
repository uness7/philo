/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:28:07 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/19 11:37:49 by yzioual          ###   ########.fr       */
/*   Updated: 2024/02/16 16:43:15 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_status(t_philo *philo, char *msg)
{
	bool	dead_or_full;

	pthread_mutex_lock(&philo->obj->mutex);
	dead_or_full = philo->obj->is_dead || philo->obj->is_full;
	pthread_mutex_unlock(&philo->obj->mutex);
	if (dead_or_full == true)
		return (false);
	printf("%lu %d %s\n", ft_time() - philo->obj->st, philo->id, msg);
	return (true);
}

bool	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (print_status(philo, "has taken a fork") == false)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (false);
	}

	pthread_mutex_lock(philo->right_fork);
	if (print_status(philo, "has taken a fork") == false)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (false);
	}
	return (true);
}

bool	sleep_think(t_philo *philo)
{
	if (print_status(philo, "is sleeping") == false)
	{
		return (false);
	}
	ft_usleep(philo->obj->time_sleep);
	if (print_status(philo, "is thinking") == false)
	{
		return (false);
	}
	return (true);
}
