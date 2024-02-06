/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:11:20 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/06 12:24:07 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf_status(t_philo *philo, char *s)
{
	printf("%lu %d %s", ft_now_ms() - philo->last_meal_beginning, philo->id, s);
}

void	ft_puterr(void)
{
	printf("Args Not Enough!\n");
	printf("You have to specify 4 arguments and last one is optional.\n");
	printf("Please enter args in this exact order!\n");
	printf("1. Number of philosophers\n");
	printf("2. Time to die (ms)\n");
	printf("3. Time to eat (ms)\n");
	printf("4. Time to sleep (ms)\n");
	printf("5. Times a philo has to eat and then die (ms) (optional)\n");
}

uint64_t	ft_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	get_args(int ac, char **av, t_obj *obj)
{
	if (ac == 5)
	{
		obj->num_philos = ft_atoi(av[1]) * 1000;
		obj->time_die = ft_atoi(av[2]) * 1000;
		obj->time_eat = ft_atoi(av[3]) * 1000;
		obj->time_sleep = ft_atoi(av[4]) * 1000;
		obj->time_think = 0;
		if (obj->num_philos % 2 && obj->time_eat * 2 - obj->time_sleep > 0)
			obj->time_think = obj->time_eat * 2 - obj->time_sleep;
	}
	if (ac == 6)
	{
		obj->num_philos = ft_atoi(av[1]) * 1000;
		obj->time_die = ft_atoi(av[2]) * 1000;
		obj->time_eat = ft_atoi(av[3]) * 1000;
		obj->time_sleep = ft_atoi(av[4]) * 1000;
		obj->times_eat_die = ft_atoi(av[5]) * 1000;
		obj->time_think = 0;
		if (obj->num_philos % 2 && obj->time_eat * 2 - obj->time_sleep)
			obj->time_think = obj->time_eat * 2 - obj->time_sleep;
	}
	obj->start_time = ft_now_ms();
}
