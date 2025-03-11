/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ml.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:16:25 by ubuntu            #+#    #+#             */
/*   Updated: 2025/03/11 22:30:13 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_nbr_words(char const *s, char c)
{
	long int		i;
	int			nbr;
	int				same_carac;

	i = 0;
	nbr = 0;
	same_carac = 0;
	while (s[i])
	{
		if (s[i] != c && same_carac == 0)
		{
			nbr++;
			same_carac = 1;
		}	
		else if (s[i] == c)
			same_carac = 0;
		i++;
	}
	return (nbr);
}

static char	*ft_alloue_and_copy_word(char const *s, int start, int end, t_mnode *ml)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc_list((end - start + 1), sizeof(char), ml);
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	return (word);
}

/* static void	*ft_free_double_tab_tab(char **tab_tab, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		free(tab_tab[i]);
		i++;
	}
	free(tab_tab);
	return (NULL);
} */

static void	ft_init(int *i, int *w, int *first_carac)
{
	*i = 0;
	*w = 0;
	*first_carac = -1;
}

char	**ft_split_ml(char const *s, char c, t_mnode *ml)
{
	char	**tab_tab;
	int		i;
	int		first_carac;
	int		w;

	tab_tab = ft_calloc_list(ft_nbr_words(s, c) + 1, sizeof(char *), ml);
	if (!tab_tab)
		return (NULL);
	ft_init(&i, &w, &first_carac);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && first_carac < 0)
			first_carac = i;
		else if ((s[i] == c || i == ft_strlen(s)) && first_carac >= 0)
		{
			tab_tab[w] = ft_alloue_and_copy_word(s, first_carac, i, ml);
			if (!tab_tab[w])
				return (ft_free_ml(ml), NULL);
			first_carac = -1;
			w++;
		}
		i++;
	}
	return (tab_tab);
}
