/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:10:40 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/07 12:44:48 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	
	philo = (t_philo *)arg;
	if (philo->meals_flag == 0)
	{
		while (1)
		{
			pickup_forks(philo);
			eat(philo);
			putdown_forks(philo);
			ft_sleep(philo);
			think(philo);
		}
	}
	else if (philo->meals_flag == 1)
	{
		while (philo->meals_eaten < philo->meals)
		{
			pickup_forks(philo);
			eat(philo);
			putdown_forks(philo);
			ft_sleep(philo);
			think(philo);
			philo->meals_eaten++;
		}
		printf("Simulation finished\n");
		exit(EXIT_SUCCESS);
		return NULL;
	}	
	return (NULL);
}

/*
static void	*is_dead(void *arg)
{
	uint64_t	elapsed_time;
	t_philo		*philo;
	struct timeval  current_time;

	philo = (t_philo *)arg;
	while (philo->has_eaten == 1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = ft_now_ms() - philo->last_meal_beginning; 
		printf("el_time : % and ti_die : %ul\n", 
				elapsed_time,
				philo->time_die)
			;
		if (elapsed_time > (uint64_t )philo->time_die)
		{
			philo->has_eaten = 0;
			ft_printf_status(philo, "died!\n");
			break ;
		}
		printf("RIP One Of Philosophers has died \n");	
		exit(EXIT_SUCCESS);
	}
	return (NULL);
}
*/



static void *is_dead(void *arg)
{
    uint64_t elapsed_time;
    t_philo *philo;
    struct timeval current_time;

    philo = (t_philo *)arg;
    while (philo->has_eaten == 0)
    {
        gettimeofday(&current_time, NULL);
	// something wrong is here
        elapsed_time = ft_now_ms() - philo->last_meal_beginning;
        if (elapsed_time > (uint64_t)philo->time_die)
        {
            philo->has_eaten = 1;
            ft_printf_status(philo, "died!\n");
            break;
        }
        printf("RIP One Of Philosophers has died \n");
        exit(EXIT_SUCCESS);
    }
    return (NULL);
}



void	ft_philo(t_obj *obj)
{
	pthread_t		timer_threads[obj->num_philos];
	pthread_t		philos_threads[obj->num_philos];
	pthread_mutex_t		forks[obj->num_philos];
	t_philo			philo[obj->num_philos];
	int				i;

	init_philo(philo, obj);
	i = 0;
	while (i < obj->num_philos)
	{
		philo[i].id = i;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % obj->num_philos];
		pthread_mutex_init(&forks[i], NULL);
		pthread_create(&philos_threads[i], NULL, &routine, &philo[i]);
		pthread_create(&timer_threads[i], NULL, &is_dead, &philo[i]);
		i++;
	}
	i = -1;
	while (++i < obj->num_philos)
		pthread_join(philos_threads[i], NULL);
	i = -1;
	while (++i < obj->num_philos)
		pthread_join(timer_threads[i], NULL);

	i = -1;
	while (++i < obj->num_philos)
		pthread_detach(philos_threads[i]);
	i = -1;
	while (++i < obj->num_philos)
		pthread_mutex_destroy(&forks[i]);
}
