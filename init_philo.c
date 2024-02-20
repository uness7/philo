/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:21:01 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/17 16:36:33 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	init_obj(int ac, char **av, t_obj *obj)
{
	obj->num_philos = ft_atoi(av[1]);
	if (obj->num_philos > 200)
	{
		printf("Bruh! it's WAY TOO MANY PHILOSOPHERS\n");
		exit(1);
	}
	obj->time_die = ft_atoi(av[2]);
	obj->time_eat = ft_atoi(av[3]);
	obj->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		obj->max_meals = ft_atoi(av[5]);
		if (obj->max_meals == 0)
		{
			printf("Bruh! You can't enter 0 as max meals :*\n");
			ft_puterr();
		}
	}
	else if (ac == 5)
		obj->max_meals = -1;
	pthread_mutex_init(&obj->mutex, NULL);
	obj->st = ft_time();
}

static void	init_philo(t_obj *obj)
{
	int				i;

	i = -1;
	while (++i < obj->num_philos)
	{
		obj->philos[i].id = i + 1;
		obj->philos[i].lmb = obj->st;
		pthread_mutex_init(&obj->philos[i].left_fork, NULL);
		obj->philos[i].right_fork = &obj->philos[(i + 1) % obj->num_philos].left_fork;
		obj->philos[i].obj = obj;
	}
	obj->philos[obj->num_philos - 1].right_fork = &obj->philos[0].left_fork;
}

void	init(int ac, char **av, t_obj *obj)
{
	init_obj(ac, av, obj);
	init_philo(obj);
}
