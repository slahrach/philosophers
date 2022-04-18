/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:56:32 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/16 02:57:00 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	current;
	long long		time;

	gettimeofday(&(current), NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time);
}

static int	checker(t_strct *data, int *check, int *j)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		if (data->opt != -1 && data->philos[i].n_meals == data->opt
			&& !check[i])
		{
			check[i] = 1;
			(*j)++;
		}
		if (timestamp() - data->philos[i].last_meal >= data->t_to_die)
		{
			messages(&data->philos[i], "died");
			data->dead = 1;
			destroy(data, check);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, const char	**argv)
{
	int		j;
	int		*check;
	t_strct	data;

	if (init_args(&data, argv, argc))
		return (0);
	create_mutexes(&data);
	create_threads(&data);
	check = malloc (sizeof (int) * (data.philo_nbr));
	memset(check, 0, (data.philo_nbr) * sizeof (int));
	j = 0;
	while (!data.all)
	{
		if (checker(&data, check, &j))
			return (0);
		if (j == data.philo_nbr)
			data.all = 1;
	}
	destroy(&data, check);
	return (0);
}
