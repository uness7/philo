#include "philo.h"

int	main(int ac, char **av)
{
	t_obj	obj;

	if (ac == 5 || ac == 6)
	{
		if (is_input_valid(ac, av))
		{
			get_args(ac, av, &obj);
			ft_philo(&obj);
		}
	}
	else
		ft_puterr();
	return (0);
}
