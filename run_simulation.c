#include "philo.h"

static void     _routine(t_philo *philo)
{
        while (1)
        {
                if (!pickup_forks(philo))
                        break ;
		increment_meals_update_lmb(philo);
                print_status(philo, "is eating 🍝");
                ft_usleep(philo->obj->time_eat);
		update_meals_count(philo);
		release_forks(philo);
		if (!ft_sleep_think(philo))
                        break ;
        }
}

void     *routine(void *data)
{
        t_philo *philo;

        philo = (t_philo *)data;
	// Delay for even philosophers number to avoid simultaneous actions
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
