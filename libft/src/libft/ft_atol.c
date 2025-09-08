/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/17 00:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	handle_overflow(int sign)
{
	if (sign == 1)
		return (9223372036854775807L);
	return ((long)-9223372036854775807LL - 1);
}

long	ft_atol(const char *nptr)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (ft_isdigit(nptr[i]))
	{
		if (result > (9223372036854775807L - (nptr[i] - '0')) / 10)
			return (handle_overflow(sign));
		result = result * 10 + (nptr[i++] - '0');
	}
	return (result * sign);
}
