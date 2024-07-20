/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:43:29 by mawad             #+#    #+#             */
/*   Updated: 2024/05/10 17:43:32 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	spcsign_loop(const char *nptr, int *i, int *negative_flag)
{
	while ((nptr[*i] >= 9 && nptr[*i] <= 13) || nptr[*i] == 32)
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			*negative_flag *= -1;
		(*i)++;
	}
}

long long int	ft_atol(const char *nptr)
{
	int				i;
	int				negative_flag;
	int				digit;
	long long int	store;

	i = 0;
	negative_flag = 1;
	store = 0;
	spcsign_loop(nptr, &i, &negative_flag);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - 48;
		if ((store > (9223372036854775807 - digit) / 10) && negative_flag == 1)
			return (2147483648);
		if ((store > (9223372036854775807 - digit) / 10) && negative_flag == -1)
			return (-2147483649);
		store = store * 10 + digit;
		i++;
	}
	return ((store * negative_flag));
}
