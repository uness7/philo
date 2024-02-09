#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* Text Colors */
# define RED "\033[31m"
# define GREEN "\033[32m"
# define PEACH "\033[38;5;203m"
# define WHITE "\033[37m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"

/* An object representing a philosopher. */
typedef struct s_philo
{
	int				id;
	uint64_t		last_meal_beginning;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_obj	*obj;
}					t_philo;

/* An object that holds variables */
typedef struct s_obj
{
	int				num_philos;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				max_meals;
	int				total_finished;
	int				is_dead;
	int				is_full;
	uint64_t		start_time;
	pthread_mutex_t	mutex;
	t_philo			philos[200];
}					t_obj;

void				*routine(void *arg);
void				ft_puterr(void);
int					ft_print(t_philo *philo, char *s);
void				init(int ac, char **av, t_obj *obj);

int					ft_break_while(t_obj *obj, int *i);
int					ft_write_status(t_philo *philo, char *msg);
int					ft_should_stop(t_philo *philo);
int					pickup_forks(t_philo *philo);
int					ft_sleep_think(t_philo *philo);

void				get_args(int ac, char **av, t_obj *obj);

uint64_t			ft_now_ms(void);

int					is_input_valid(int ac, char **av);
int					ft_atoi(char *s);

#endif
