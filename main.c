/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:56:32 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/12 02:59:54 by slahrach         ###   ########.fr       */
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
	t_strct	data;

	if (argc < 5)
		error(0);
	init_args(&data, argv, argc);
	create_mutexes(&data);
	create_threads(&data);
	destroy(&data);
}
