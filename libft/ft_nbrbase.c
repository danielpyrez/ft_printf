/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danipere <danipere@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:43:13 by danipere          #+#    #+#             */
/*   Updated: 2026/06/30 15:40:36 by danipere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrbase_len(long long nbr, int based)
{
	int	count;

	count = 0;
	while (True)
	{
		nbr = nbr / based;
		count++;
		if (nbr < based)
			break ;
	}
	return (count + 1);
}

char	*ft_nbrbase(long long nbr, char *base)
{
	int		based;
	char	*res;
	int		nbr_len;
	int		i;
	int		neg;

	i = -1;
	neg = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		neg = 1;
	}
	based = ft_strlen(base);
	nbr_len = nbrbase_len(nbr, based);
	res = malloc((nbr_len + neg + 1) * sizeof(char));
	while (++i < nbr_len)
	{
		res[i] = base[nbr % based];
		nbr /= based;
	}
	res[i + neg] = 0;
	if (neg)
		res[i] = '-';
	return (ft_strreverse(res));
}
