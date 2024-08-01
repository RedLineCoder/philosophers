/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:06 by moztop            #+#    #+#             */
/*   Updated: 2024/08/01 22:07:15 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
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
	u_int32_t	num;

	num = 0;
	if (!str)
		return (num);
	while (*str == ' ' || (*str <= '\r' && *str >= '\t'))
		str++;
	while (*str <= 9 && *str >= 0)
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

int	init_philos(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->philo_count)
	{
		main->philosophers[i].index = i;
		main->philosophers[i].diestamp = main->started + main->time_to_die;
		if (pthread_mutex_init(&main->philosophers[i].m_fork, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&main->philosophers[i].m_diestamp, NULL) != 0)
			return (0);
		if (pthread_create(main->philosophers[i].thread, NULL, philo_routine,
				&main->philosophers[i]) != 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_main *const	main = &(t_main){0};

	if (!check_args(argc, argv))
		return (1);
	main->philo_count = ft_atoui32(argv[1]);
	main->time_to_die = ft_atoui32(argv[2]);
	main->time_to_eat = ft_atoui32(argv[3]);
	main->time_to_sleep = ft_atoui32(argv[4]);
	main->must_eat_count = -1;
	if (argc == 6)
		main->must_eat_count = ft_atoui32(argv[5]);
	main->started = get_timestamp();
	if (!main->started)
		return (write(2, "Timestamp initialization error!\n", 32), 1);
	if (!init_philos(main))
		return (write(2, "Philosopher initialization error!\n", 34), 1);
	return (0);
}
