/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:03:19 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/12 21:30:33 by slahrach         ###   ########.fr       */
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

void	messages(t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->data->lktaba);
	if (a == 1)
		printf("%lld %d has taken fork\n", timestamp(), philo->index);
	else if (a == 2)
		printf("%lld %d is eating\n", timestamp(), philo->index);
	else if (a == 3)
		printf("%lld %d is sleeping\n", timestamp(), philo->index);
	else if (a == 4)
		printf("%lld %d is thinking\n", timestamp(), philo->index);
	pthread_mutex_unlock(&philo->data->lktaba);
}
