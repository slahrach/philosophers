/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:03:19 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/16 02:45:17 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	messages(t_philo *philo, char *str)
{
	long long	start;

	start = philo->data->start;
	pthread_mutex_lock(&philo->data->lktaba);
	if (philo->data->dead || philo->data->all)
		return ;
	printf("%lld %d %s\n", timestamp() - start, philo->index, str);
	pthread_mutex_unlock(&philo->data->lktaba);
}
