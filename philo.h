#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>

/* Text Colors */
#define RED "\033[31m"
#define GREEN "\033[32m"
#define PEACH "\033[38;5;203m"  // Bright yellowish-red (approximation for peach)
#define WHITE "\033[37m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

/* Status */
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

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
	int				has_eaten;
	int				meals_max;
	uint64_t		last_meal_beginning;
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
	int				meals_max;
	uint64_t		start_time;
}					t_obj;

void				think(t_philo *philo);
void				eat(t_philo *philo);
void				*routine(void *arg);
void				*timer_routine(void *arg);
void				ft_sleep(t_philo *philo);
void				ft_puterr(void);
void				ft_printf_status(t_philo *philo, char *s);
void				putdown_forks(t_philo *philo);
void				pickup_forks(t_philo *philo);
void				get_args(int ac, char **av, t_obj *obj);

uint64_t			ft_now_ms(void);

int					is_input_valid(int ac, char **av);
int					ft_atoi(char *s);

#endif
