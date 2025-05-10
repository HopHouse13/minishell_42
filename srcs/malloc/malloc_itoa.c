/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:14:29 by pab               #+#    #+#             */
/*   Updated: 2025/05/10 22:18:45 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_size(long int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_ml(int n, t_mnode **ml)
{
	long int	nb;
	size_t		count;
	char		*str;

	nb = n;
	count = count_size(nb);
	if (n < 0)
		count++;
	str = ft_malloc_list(sizeof(char) * count +1, ml);
	if (!str)
		return (NULL);
	str[count] = '\0';
	if (nb == 0)
		(str[0] = '0');
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	while (nb)
	{
		str[--count] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}