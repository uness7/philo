/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:11:12 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/07 12:42:18 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	ft_printf_status(philo, "is thinking 🧠\n");
	usleep(6000);
}

void	eat(t_philo *philo)
{
	philo->last_meal_beginning = ft_now_ms();
	printf(GREEN);
	ft_printf_status(philo, "is eating 🍜 \n");
	printf(WHITE);
	usleep(philo->time_eat);
}

void	ft_sleep(t_philo *philo)
{
	printf(BLUE);
	ft_printf_status(philo, "is sleeping 💤 \n");
	printf(WHITE);
	usleep(philo->time_sleep);
}

int	is_input_valid(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + (s[i++] - '0');
	return (result);
}
