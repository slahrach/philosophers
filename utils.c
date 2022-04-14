/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:15:15 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/14 03:31:12 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static	int	ret(int sign, long n)
{
	if (n >= 2147483648U && sign == 1)
		return (0);
	if (n >= 2147483649U && sign == -1)
		return (0);
	return (n * sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	nbr;

	if (ft_strlen(str) > 10)
		return (0);
	sign = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' )
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (*str)
		return (0);
	return (ret(sign, nbr));
}

void	t_sleep(int time, t_strct *data)
{
	int			i;
	long long	time0;

	i = 0;
	time0 = timestamp();
	while (!data->dead)
	{
		if (timestamp() - time0 >= time)
			break ;
		usleep(500);
	}
}
