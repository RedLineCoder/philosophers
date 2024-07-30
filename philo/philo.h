/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:10 by moztop            #+#    #+#             */
/*   Updated: 2024/07/30 15:08:58 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

typedef enum e_action
{
	DIE,
	THINK,
	FORK,
	EAT,
	SLEEP
}						t_action;

# define MSG_DIE "died"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"

// sysctl kern.num_taskthreads

# define MAX_PHILO 2048

typedef struct s_philo
{
	unsigned long long	timestamp;
	int					index;
	int					queue;
	pthread_mutex_t		fork;

}						t_philo;

typedef struct s_main
{
	t_philo				philosophers[2048];
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat_count;
}						t_main;

#endif