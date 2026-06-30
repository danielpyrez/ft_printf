/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_nbrbase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danipere <danipere@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:43:13 by danipere          #+#    #+#             */
/*   Updated: 2026/06/29 23:20:28 by danipere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrbase_len(unsigned long nbr, unsigned long based)
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

char	*ft_unsigned_nbrbase(unsigned long nbr, char *base)
{
	int				rem;
	char			*res;
	int				nbr_len;
	int				i;
	unsigned long	based;

	i = 0;
	based = ft_strlen(base);
	nbr_len = nbrbase_len(nbr, based);
	res = malloc((nbr_len + 1) * sizeof(char));
	while (i < nbr_len)
	{
		rem = nbr % based;
		nbr = nbr / based;
		res[i] = base[rem];
		i++;
	}
	res[i] = 0;
	ft_strreverse(res);
	return (res);
}
