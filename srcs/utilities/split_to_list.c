/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:47:14 by pbret             #+#    #+#             */
/*   Updated: 2025/03/02 18:16:41 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_strncpy(char *str1, char *str2, int nb)
{
	int	i;

	i = 0;
	while (i < nb && str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return ;
}

int	ft_count_words(char *str)
{
	int		i;
	int		word;
	int		flag;

	i = 0;
	word = 0;
	flag = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
		{
			flag = 1;
			i++;
		}
		if (flag == 1)
		{
			flag = 0;
			word += 1;
		}
	}
	return (word);
}

char	**ft_initialisation_tab(char **tab, char *str)
{
	int		i;
	int		start;
	int		j;

	i = 0;
	j = 0;
	start = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		start = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
		if (i > start)
		{
			tab[j] = malloc(sizeof(char) * (i - start + 1));
			ft_strncpy(tab[j], &str[start], (i - start));
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_argv(char *str)
{
	char	**tab;
	int		nb_words;

	nb_words = ft_count_words(str);
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	ft_initialisation_tab(tab, str);
	return (tab);
}