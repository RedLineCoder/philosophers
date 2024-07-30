/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:06 by moztop            #+#    #+#             */
/*   Updated: 2024/07/30 17:15:01 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	check_args(int argc, char **argv)
{
	int	index;
	int	loop;

	if (argc != 5 && argc != 6)
		return (printf("Argument count error !"), 0);
	index = 0;
	while (argv[++index])
	{
		loop = -1;
		while (argv[index][++loop])
		{
			if (argv[index][loop] > '9' || argv[index][loop] < '0')
				return (printf("Argument type <int(+)::miliseconds>"));
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

void	init_main(t_main *main, int argc, char **argv)
{
	main->philo_count = ft_atoui32(argv[1]);
	main->time_to_die = ft_atoui32(argv[2]);
	main->time_to_eat = ft_atoui32(argv[3]);
	main->time_to_sleep = ft_atoui32(argv[4]);
	main->max_eat_count = -1;
	if (argc == 6)
		main->max_eat_count = ft_atoui32(argv[5]);
}

int	main(int argc, char **argv)
{
	t_main *const main = &(t_main){0};

	if (!check_args(argc, argv))
		return (1);
	init_main(main, argc, argv);
	return (0);
}
