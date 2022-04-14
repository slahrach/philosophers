/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:23:18 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/13 23:11:01 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy(t_strct *data)
{
	int	i;

	i = 0;
	while (++i <= data->philo_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&data->lktaba);
}

void	*process(void *philo_v)
{
	t_strct	*data;
	t_philo	*philo;
	int		id;

	philo = (t_philo *) philo_v;
	data = philo->data;
	if (data->philo_nbr == 1)
		return (NULL);
	id = philo->index;
	if (id % 2 == 0)
		usleep(1500);
	while (!data->dead && !data->all)
	{
		pthread_mutex_lock(&data->forks[philo->fork_right]);
		pthread_mutex_lock(&data->forks[philo->fork_left]);
		messages(philo, 1);
		messages(philo, 1);
		messages(philo, 2);
		philo->last_meal = timestamp();
		if (data->opt != -1)
			philo->n_meals++;
		t_sleep(data->t_to_eat, data);
		pthread_mutex_unlock(&data->forks[philo->fork_right]);
		pthread_mutex_unlock(&data->forks[philo->fork_left]);
		messages(philo, 3);
		t_sleep(data->t_to_sleep, data);
		messages(philo, 4);
	}
	return (NULL);
}

void	create_threads(t_strct *data)
{
	int		i;

	i = 0;
	while (++i <= data->philo_nbr)
		pthread_create(&(data->philos[i].th), NULL, &process, &data->philos[i]);
	i = 0;
	while (++i <= data->philo_nbr)
		pthread_detach(data->philos[i].th);
}
