/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:10:59 by yzioual           #+#    #+#             */
/*   Updated: 2024/02/06 12:20:33 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/* Text Colors */
#define RED "\033[31m"
#define GREEN "\033[32m"
#define PEACH "\033[38;5;203m"
#define WHITE "\033[37m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

/* An object representing a philosopher. */
typedef struct s_philo
{
	int				id;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				time_think;
	int				has_eaten;
	uint64_t		last_meal_beginning;
	int				meals;
	int				meals_eaten;
	int				dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

/* An object that holds variables */
typedef struct s_obj
{
	int				num_philos;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				times_eat_die;
	int				time_think;
	uint64_t		start_time;
}					t_obj;

void				think(t_philo *philo);
void				eat(t_philo *philo);
void				ft_philo(t_obj *obj);
// void				*routine(void *arg);
// void				*timer_routine(void *arg);
void				ft_sleep(t_philo *philo);
void				ft_puterr(void);
void				ft_printf_status(t_philo *philo, char *s);
void				putdown_forks(t_philo *philo);
void				pickup_forks(t_philo *philo);
void				get_args(int ac, char **av, t_obj *obj);
void				break_loop(t_philo *philo);
void				init_philo(t_philo philo[], t_obj *obj);
void				init_threads(t_philo philo[], t_obj *obj, pthread_t philos_threads[], pthread_t timer_threads[], pthread_mutex_t forks[]);

uint64_t			ft_now_ms(void);

int					is_input_valid(int ac, char **av);
int					ft_atoi(char *s);

#endif
