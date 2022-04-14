/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:09:22 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/13 23:09:36 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_args(t_strct *data, char **argv, int argc)
{
	int	i;

	i = 0;
	data->philo_nbr = ft_atoi(argv[1]);
	if (!data->philo_nbr || data->philo_nbr > 200)
		error(1);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->opt = ft_atoi(argv[5]);
	else
		data->opt = -1;
	if (!data->t_to_die || !data->t_to_eat || !data->t_to_sleep)
		error(1);
	data->philos = (t_philo *) malloc (data->philo_nbr * sizeof (t_philo));
	data->start = timestamp();
	while (++i <= data->philo_nbr)
		data->philos[i].index = i;
	i = 0;
	while (++i <= data->philo_nbr)
		data->philos[i].last_meal = timestamp();
	i = 0;
	while (++i <= data->philo_nbr)
	{
		data->philos[i].n_meals = 0;
		data->philos[i].data = data;
	}
	data->dead = 0;
	data->all = 0;
}

void	create_mutexes(t_strct *data)
{
	int	i;

	pthread_mutex_init(&(data->lktaba), NULL);
	//pthread_mutex_init(&data->meal, NULL);
	i = 0;
	data->forks = malloc (data->philo_nbr * sizeof (pthread_mutex_t));
	while (++i <= data->philo_nbr)
		pthread_mutex_init(&(data->forks[i]), NULL);
	data->philos[1].fork_right = data->philos[1].index;
	if (data->philo_nbr > 1)
		data->philos[1].fork_left = data->philos[data->philo_nbr].index;
	i = 1;
	while (++i <= data->philo_nbr)
	{
		data->philos[i].fork_right = data->philos[i].index;
		data->philos[i].fork_left = data->philos[i - 1].index;
	}
}
