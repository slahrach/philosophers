/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:56:32 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/13 01:22:25 by slahrach         ###   ########.fr       */
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

int	main(int argc, char	**argv)
{
	int		*check;
	int		all;
	int		i;
	t_strct	data;

	if (argc < 5)
		error(0);
	init_args(&data, argv, argc);
	create_mutexes(&data);
	create_threads(&data);
	check = (int *) malloc (sizeof (int) * (data.philo_nbr + 1));
	memset(check, 0, (data.philo_nbr + 1) * sizeof (int));
	all = 0;
	while (1)
	{
		i = 0;
		while (++i <= data.philo_nbr)
		{
			if (data.opt != -1 && data.philos[i].n_meals == data.opt && !check[i])
			{
				check[i] = 1;
				all++;
			}
			if (timestamp() - data.philos[i].last_meal >= data.t_to_die)
			{
				printf("%lld %d died\n", timestamp(), data.philos[i].index);
				destroy(&data);
				return (0);
			}
		}
		if (all == data.philo_nbr)
			return (0);
	}
}
