/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:09:22 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/16 02:58:08 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_errors(t_strct *data, const char **argv, int argc)
{
	if (argc < 5)
	{
		write (2, "Number of arguments is invalid\n", 32);
		return (1);
	}
	if (data->philo_nbr <= 0 || data->philo_nbr > 200 || data->t_to_die <= 0
		|| data->t_to_eat <= 0 || data->t_to_sleep <= 0
		|| (argc == 6 && data->opt <= 0 && ft_strcmp(argv[argc - 1], "0")))
	{
		write (2, "Error in Args\n", 44);
		return (1);
	}
	return (0);
}

static void	init_philo(t_strct *data)
{
	int	i;

	i = -1;
	data->philos = (t_philo *) malloc ((data->philo_nbr) * sizeof(t_philo));
	while (++i < data->philo_nbr)
		data->philos[i].index = i + 1;
	i = -1;
	while (++i < data->philo_nbr)
		data->philos[i].last_meal = timestamp();
	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philos[i].n_meals = 0;
		data->philos[i].data = data;
	}
}

int	init_args(t_strct *data, const char **argv, int argc)
{
	data->philo_nbr = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->opt = ft_atoi(argv[5]);
	else
		data->opt = -1;
	if (check_errors(data, argv, argc))
		return (1);
	init_philo(data);
	data->dead = 0;
	data->all = 0;
	return (0);
}

void	create_mutexes(t_strct *data)
{
	int	i;

	pthread_mutex_init(&(data->lktaba), NULL);
	i = -1;
	data->forks = malloc ((data->philo_nbr) * sizeof (pthread_mutex_t));
	while (++i < data->philo_nbr)
		pthread_mutex_init(&(data->forks[i]), NULL);
	data->philos[0].fork_right = data->philos[0].index;
	data->philos[0].fork_left = data->philos[data->philo_nbr - 1].index;
	i = 0;
	while (++i < data->philo_nbr)
	{
		data->philos[i].fork_right = data->philos[i].index;
		data->philos[i].fork_left = data->philos[i - 1].index;
	}
}
