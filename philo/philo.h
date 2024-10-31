/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moztop <moztop@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:10 by moztop            #+#    #+#             */
/*   Updated: 2024/08/08 18:46:06 by moztop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define MSG_DIE "died"
# define MSG_THINK "is thinking"
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"

# define INIT 0
# define START 1
# define END 2

typedef unsigned long long	t_timestamp;

typedef struct s_philo
{
	int						index;
	int						times_eaten;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	int						philo_count;
	int						*satisfied_philos;
	int						*status;
	pthread_t				thread;
	t_timestamp				diestamp;
	t_timestamp				*startstamp;
	pthread_mutex_t			*m_main;
	pthread_mutex_t			*m_msg;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
}							t_philo;

typedef struct s_main
{
	int						status;
	int						satisfied_philos;
	int						philo_count;
	t_timestamp				startstamp;
	pthread_mutex_t			m_main;
	pthread_mutex_t			m_msg;
	pthread_mutex_t			*forks;
}							t_main;

// Utils
t_timestamp					get_timestamp(void);
void						ft_usleep(t_timestamp ms);
long long					fetch_data(pthread_mutex_t *mutex, void *data,
								int size);
int							init_philo(t_philo *philo, int argc, char **argv, int i);
unsigned int				ft_atoui(char *str);

// Actions
void						*philo_routine(void *arg);


#endif
