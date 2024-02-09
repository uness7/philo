#include "philo.h"

void	ft_puterr(void)
{
	printf("Args Not Enough!\n");
	printf("You have to specify 4 arguments and last one is optional.\n");
	printf("Please enter args in this exact order!\n");
	printf("1. Number of philosophers\n");
	printf("2. Time to die (ms)\n");
	printf("3. Time to eat (ms)\n");
	printf("4. Time to sleep (ms)\n");
	printf("5. Times a philo has to eat and then die (ms) (optional)\n");
}

uint64_t	ft_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec) * 1000 + (uint64_t)(tv.tv_usec) / 1000);
}

int	is_input_valid(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + (s[i++] - '0');
	return (result);
}
