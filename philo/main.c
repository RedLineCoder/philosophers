/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:06 by moztop            #+#    #+#             */
/*   Updated: 2024/07/30 15:11:56 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	exit_safe(t_main *main, char *err)
{
	(void)main;
	printf("%s\n", err);
}

int	main(int argc, char **argv)
{
	t_main *const main = &(t_main){0};

	if (argc != 4 && argc != 5)
		return (exit_safe(main, "Argument count error."), 1);
	(void)argv;
}
