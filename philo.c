#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (is_input_valid(ac, av))
			run_simulation(ac, av);
	}
	else
		ft_puterr();
	return (0);
}
