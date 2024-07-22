/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:28:29 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/21 20:08:36 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*s3;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(len1 + len2 + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (i < len1 + len2)
	{
		if (i < len1)
			s3[i] = s1[i];
		else
			s3[i] = s2[i - len1];
		i++;
	}
	s3[len1 + len2] = '\0';
	free(s1);
	return (s3);
}
