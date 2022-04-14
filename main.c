/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:56:32 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/14 01:20:55 by slahrach         ###   ########.fr       */
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

int	checker(t_strct data, int *check, int *j)
{
	int	i;

	i = 0;
	while (++i <= data.philo_nbr)
	{
		if (data.opt != -1 && data.philos[i].n_meals == data.opt && !check[i])
		{
			check[i] = 1;
			(*j)++;
		}
		if (timestamp() - data.philos[i].last_meal >= data.t_to_die)
		{
			messages(&data.philos[i], "died");
			data.dead = 1;
			destroy(&data);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char	**argv)
{
	int		j;
	int		*check;
	t_strct	data;

	if (argc < 5)
		error(0);
	init_args(&data, argv, argc);
	create_mutexes(&data);
	create_threads(&data);
	check = malloc (sizeof (int) * (data.philo_nbr + 1));
	memset(check, 0, (data.philo_nbr + 1) * sizeof (int));
	j = 0;
	while (!data.all)
	{
		if (checker(data, check, &j))
			return (0);
		if (j == data.philo_nbr)
			data.all = 1;
	}
}
