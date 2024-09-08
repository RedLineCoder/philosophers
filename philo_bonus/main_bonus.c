/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 07:26:24 by moztop            #+#    #+#             */
/*   Updated: 2024/09/08 14:43:24 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

int	check_args(int argc, char **argv)
{
	int	index;
	int	loop;

	if (argc != 5 && argc != 6)
		return (write(2, "Argument count error!\n", 22), 0);
	index = 0;
	while (argv[++index])
	{
		loop = -1;
		while (argv[index][++loop])
		{
			if (argv[index][loop] > '9' || argv[index][loop] < '0')
				return (write(2, "Argument type <int(+)::miliseconds>\n", 36),
					0);
		}
	}
	return (1);
}

u_int32_t	ft_atoui32(char *str)
{
	u_int32_t	result;

	result = 0;
	while (*str == ' ' || (*str <= '\r' && *str >= '\t'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result);
}

t_philo	*start_philo(t_main *main, int index)
{
	t_philo	*philo;
	int		i;

	if (!main->philo_count)
		return (0);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	memset(philo, 0, sizeof(t_philo));
	philo->index = index;
	philo->main = main;
	if (!pthread_create(&(philo->thread), NULL, philo_routine, (void *)&(philo)) != 0)
		return (free(philo));
}

int	main(int argc, char **argv)
{
	t_main *const	main = &(t_main){0};

	main->sem = sem_open("sem", O_CREAT | O_EXCL, O_RDWR, main->philo_count);
	if (!check_args(argc, argv))
		return (1);
	main->philo_count = ft_atoui32(argv[1]);
	main->time_to_die = ft_atoui32(argv[2]);
	main->time_to_eat = ft_atoui32(argv[3]);
	main->time_to_sleep = ft_atoui32(argv[4]);
	main->must_eat_count = -1;
	if (argc == 6)
		main->must_eat_count = ft_atoui32(argv[5]);
	main->startstamp = get_timestamp();
	return (0);
}
