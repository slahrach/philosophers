/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:56:56 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/14 04:36:29 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int						n_meals;
	int						index;
	long long				last_meal;
	pthread_t				th;
	int						fork_left;
	int						fork_right;
	struct s_strct			*data;
}	t_philo;

typedef struct s_strct
{
	int				dead;
	long long		start;
	int				all;
	int				philo_nbr;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				opt;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lktaba;
	t_philo			*philos;
}	t_strct;

void		error(int a);
void		init_args(t_strct *data, const char **argv, int argc);
int			ft_atoi(const char *str);
long long	timestamp(void);
void		check_args(t_strct *data, char **argv, int argc);
void		create_mutexes(t_strct *data);
void		destroy(t_strct *data, int *check);
void		create_threads(t_strct *data);
void		messages(t_philo *philo, char *str);
void		t_sleep(int time, t_strct *data);
int			ft_strcmp(const char *s1, const char *s2);

#endif