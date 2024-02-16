#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
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
	uint64_t		lmb;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
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
	uint64_t		st;
	pthread_mutex_t	mutex;
	t_philo			philos[200];
}					t_obj;

void				run_simulation(int ac, char **av);
void				init_simulation(int ac, char **av, t_obj *obj);
void				create_threads(t_obj *obj);
void				wait_for_threads_finish(t_obj *obj);
void				check_simulation_end(t_obj *obj);
void				cleanup_mutex(t_obj *obj);

void				*routine(void *data);
void				increment_meals_update_lmb(t_philo *philo);
void				update_meals_count(t_philo *philo);
void				release_forks(t_philo *philo);

void				ft_puterr(void);
void				init(int ac, char **av, t_obj *obj);
void				ft_usleep(uint64_t milli);

bool				ft_break_while(t_obj *obj, int *i);
bool				print_status(t_philo *philo, char *msg);
bool				check_state(t_philo *philo);
bool				pickup_forks(t_philo *philo);
bool				sleep_think(t_philo *philo);
bool				check_simulation_state(t_obj *obj, int *i);

uint64_t			ft_time(void);

int					ft_print(t_philo *philo, char *s);
bool				is_input_valid(int ac, char **av);
int					ft_atoi(char *s);

#endif
