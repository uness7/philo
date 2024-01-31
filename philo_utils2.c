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
