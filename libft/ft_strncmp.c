/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:30:11 by rohoarau          #+#    #+#             */
/*   Updated: 2021/10/22 16:16:36 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, t_size n)
{
	t_size				i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (ft_isascii(s1[i]) == 0 || ft_isascii(s2[i]) == 0)
			return (1);
		if (s1[i] - s2[i] == 0)
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
