#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* An object representing a philosopher. */
typedef struct s_philo
{
	int				id;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				is_thinking;
	int				is_sleeping;
	int				is_eating;
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
}					t_obj;

void				think(t_philo *philo);
void				eat(t_philo *philo);
void				*routine(void *arg);
void				ft_sleep(t_philo *philo);
void				ft_puterr(void);
void				putdown_forks(t_philo *philo);
void				pickup_forks(t_philo *philo);

int					is_input_valid(int ac, char **av);
int					ft_atoi(char *s);

#endif
