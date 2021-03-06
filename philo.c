/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:23:18 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/16 02:56:17 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy(t_strct *data, int *check)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&data->lktaba);
	free(check);
	free(data->philos);
	free(data->forks);
}

void	to_eat(t_philo *philo, t_strct *data)
{
	pthread_mutex_lock(&data->forks[philo->fork_right]);
	messages(philo, "has taken a fork");
	if (data->all || data->dead)
		return ;
	pthread_mutex_lock(&data->forks[philo->fork_left]);
	messages(philo, "has taken a fork");
	messages(philo, "is eating");
	philo->last_meal = timestamp();
	t_sleep(data->t_to_eat, data);
	if (data->opt != -1)
		philo->n_meals++;
	pthread_mutex_unlock(&data->forks[philo->fork_right]);
	pthread_mutex_unlock(&data->forks[philo->fork_left]);
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
	while (!data->dead && !data->all)
	{
		to_eat(philo, data);
		messages(philo, "is sleeping");
		if (data->all || data->dead)
			return (NULL);
		t_sleep(data->t_to_sleep, data);
		messages(philo, "is thinking");
	}
	return (NULL);
}

void	create_threads(t_strct *data)
{
	int		i;

	i = -1;
	data->start = timestamp();
	while (++i < data->philo_nbr)
		pthread_create(&(data->philos[i].th), NULL, &process, &data->philos[i]);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_detach(data->philos[i].th);
}
