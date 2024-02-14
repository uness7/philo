#include "philo.h"

static void     _routine(t_philo *philo)
{
        while (1)
        {
                if (!pickup_forks(philo))
                        break ;
                pthread_mutex_lock(&philo->obj->mutex);
                philo->meals++;
                philo->lmb = ft_time();
                pthread_mutex_unlock(&philo->obj->mutex);
                ft_write_status(philo, "is eating 🍝");
                ft_usleep(philo->obj->time_eat);
                pthread_mutex_lock(&philo->obj->mutex);
                if (philo->meals == philo->obj->max_meals)
                        philo->obj->total_finished += (philo->obj->max_meals != -1);
                pthread_mutex_unlock(&philo->obj->mutex);
                pthread_mutex_unlock(&philo->left_fork);
                pthread_mutex_unlock(philo->right_fork);
                if (!ft_sleep_think(philo))
                        break ;
        }
}

void     *routine(void *data)
{
        t_philo *philo;

        philo = (t_philo *)data;
        if (!(philo->id & 1))
                ft_usleep(10);
        _routine(philo);
        return (NULL);
}

void    run_simulation(int ac, char **av)
{
        t_obj   obj;

	init_simulation(ac, av, &obj);	
	create_threads(&obj);
	check_simulation_end(&obj);
	wait_for_threads_finish(&obj);
	cleanup_mutex(&obj);
}
