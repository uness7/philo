/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:21:01 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/15 12:39:09 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	init_obj(int ac, char **av, t_obj *obj)
{
	obj->num_philos = ft_atoi(av[1]);
	if (obj->num_philos > 200)
	{
		ft_puterr();
	}
	obj->time_die = ft_atoi(av[2]);
	obj->time_eat = ft_atoi(av[3]);
	obj->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		obj->max_meals = ft_atoi(av[5]);
		if (obj->max_meals == 0)
		{
			ft_puterr();
		}
	}
	else if (ac == 5)
		obj->max_meals = -1;
	pthread_mutex_init(&obj->mutex, NULL);
	obj->st = ft_time();
}

/* Determines the right fork of the philosopher:
	If the philosopher is the last one (i.e., i + 1 == obj->num_philos),
	it sets the right fork to be the left fork of the first philosopher 
	(obj->philos[0].left_fork).
	Otherwise, it sets the right fork to be the left fork of the next 
	philosopher (obj->philos[i + 1].left_fork).
 */

static void	init_philo(t_obj *obj)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * obj->num_philos);
	while (++i < obj->num_philos)
	{
		obj->philos[i].id = i + 1;
		obj->philos[i].lmb = obj->st;
		pthread_mutex_init(&forks[i], NULL);
		obj->philos[i].right_fork = &obj->philos[(i + 1) % obj->num_philos].left_fork;
		obj->philos[i].obj = obj;
	}
	obj->philos[obj->num_philos - 1].right_fork = &obj->philos[0].left_fork;
	free(forks);
}

void	init(int ac, char **av, t_obj *obj)
{
	init_obj(ac, av, obj);
	init_philo(obj);
}
