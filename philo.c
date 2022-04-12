/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:23:18 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/12 02:56:21 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy(t_strct *data)
{
	int	i;

	i = 0;
	while (++i <= data->philo_nbr)
	{
		pthread_detach(data->philos[i].th);
	}
	i = 0;
	while (++i <= data->philo_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->lktaba);
}

void	*process(void *philo_v)
{
	t_strct	*data;
	t_philo	*philo;
	int		id;

	philo = (t_philo *) philo_v;
	data = philo->data;
	id = philo->index;
	if (id % 2 == 0)
		usleep(1500);
	while (1)
	{
		pthread_mutex_lock(&data->forks[philo->fork_right]);
		messages(philo, 1);
		pthread_mutex_lock(&data->forks[philo->fork_left]);
		messages(philo, 1);
		messages(philo, 2);
		philo->last_meal = timestamp();
		usleep(data->t_to_eat * 1000);
		pthread_mutex_unlock(&data->forks[philo->fork_right]);
		pthread_mutex_unlock(&data->forks[philo->fork_left]);
		messages(philo, 3);
		usleep(data->t_to_sleep * 1000);
		messages(philo, 4);
	}
	return (philo_v);
}

void	*boss(void *data_v)
{
	t_strct	*data;
	int		i;

	data = (t_strct *)data_v;
	while (1)
	{
		i = 0;
		while (++i <= data->philo_nbr)
		{
			if (timestamp() - data->philos[i].last_meal >= data->t_to_die)
			{
				printf("%lld %d died\n", timestamp(), data->philos[i].index);
				exit(0);
			}
		}
	}
	return (data_v);
}

void	create_threads(t_strct *data)
{
	int		i;

	i = 0;
	while (++i <= data->philo_nbr)
		pthread_create(&(data->philos[i].th), NULL, &process, &data->philos[i]);
	pthread_create(&data->super_th, NULL, &boss, data);
	pthread_join(data->super_th, NULL);
}
