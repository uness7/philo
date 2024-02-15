/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:10:40 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/15 12:37:27 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Step One */
int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (is_input_valid(ac, av))
		{
			run_simulation(ac, av);
		}
	}
	else
	{
		ft_puterr();
	}
	return (0);
}
