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
typedef struct s_main		t_main;

typedef struct s_philo
{
	int						index;
	int						times_eaten;
	int						satisfied;
	t_main					*main;
	pthread_t				thread;
	t_timestamp				diestamp;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			m_diestamp;
	pthread_mutex_t			m_times_eaten;
}							t_philo;

typedef struct s_main
{
	int						status;
	int						satisfied_philos;
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	t_timestamp				startstamp;
	pthread_mutex_t			m_status;
	t_philo					*philosophers;
	pthread_mutex_t			*forks;
}							t_main;

t_timestamp					get_timestamp(void);
int							init_philo(t_main	*main, int i);
void						destroy_philos(t_main *main, int size);
void						ft_usleep(t_timestamp ms);
void						*philo_routine(void *arg);
void						philo_eat(t_philo *philo);
void						philo_sleep_think(t_philo *philo);
void						join_philos(t_main *main);
void						end_checker(t_main *main);
int							check_end(t_philo *philo);
long long					fetch_data(pthread_mutex_t *mutex, void *data,
								int size);

#endif
