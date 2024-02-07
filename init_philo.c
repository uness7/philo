/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:21:01 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/07 12:42:39 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo philo[], t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->num_philos)
	{
		philo[i].time_sleep = obj->time_sleep;
		philo[i].time_eat = obj->time_eat;
		philo[i].time_die = obj->time_die;
		philo[i].has_eaten = 0;
		philo[i].dead = 0;
		philo[i].time_think = obj->time_think;
		philo[i].meals = obj->times_eat_die;
		philo[i].meals_flag = obj->meals_flag;
		philo[i].meals_eaten = 0;
		i++;
	}
}
