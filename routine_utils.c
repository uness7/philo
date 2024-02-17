/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:14:50 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/16 16:17:56 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_meals_update_lmb(t_philo *philo)
{
	pthread_mutex_lock(&philo->obj->mutex);
	philo->meals++;
	philo->lmb = ft_time();
	pthread_mutex_unlock(&philo->obj->mutex);
}

void	update_meals_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->obj->mutex);
	if (philo->obj->max_meals != -1 && philo->meals == philo->obj->max_meals)
	{
		philo->obj->num_philos_finished_max_meals++;
	}
	pthread_mutex_unlock(&philo->obj->mutex);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
