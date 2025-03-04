/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:54 by pbret             #+#    #+#             */
/*   Updated: 2025/03/04 17:16:49 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_double_tab(char **tab)
{
	int	i;

	i = -1;
	if(tab)
	{
		while (tab[++i])
			ft_printf("%s\n", tab[i]);
		ft_printf("------------------------------------------------------------\n\n");
	}
}

void	ft_print_list_tokens(t_token *head) // A SUPP
{
    t_token *tmp = head;
	ft_printf("---------- LIST_TOKENS ----------\n\n");
    while ( tmp)
    {
        ft_printf("Token: [%s]\t\t\tType: [%d]\n", tmp->elem, tmp->token);
        tmp = tmp->next;
    }
	ft_printf("\n---------------------------------\n\n");
}