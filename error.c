/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:03:19 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/14 00:25:28 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(int a)
{
	if (a == 0)
		write(2, "Number of arguments is invalid !", 33);
	else if (a == 1)
		write (2, "Args Error", 11);
	exit(0);
}

void	messages(t_philo *philo, char *str)
{
	long long	start;

	start = philo->data->start;
	if (philo->data->dead || philo->data->all)
		return ;
	pthread_mutex_lock(&philo->data->lktaba);
	printf("%lld %d %s\n", timestamp() - start, philo->index, str);
	pthread_mutex_unlock(&philo->data->lktaba);
}
