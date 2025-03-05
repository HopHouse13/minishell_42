/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:54 by pbret             #+#    #+#             */
/*   Updated: 2025/03/05 16:21:09 by pbret            ###   ########.fr       */
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
		ft_printf("\n---------------------------------\n\n");
	}
}

const char	*ft_get_name_type(t_type type)
{
	const char *type_tab[] = { "WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "HD",
							"END_HD", "APPEND", "DOLLAR", "END", "UNKNOWN"};
	
	if ( type >= WORD && type <=UNKNOWN)
		return (type_tab[type]);
	return ("INVALID_TYPE");
}

void	ft_print_list_token
(t_token *head) // A SUPP
{
    t_token *tmp = head;
	ft_printf("---------- list_token----------\n\n");
    while (tmp)
    {
        ft_printf("Token: [%s]\t\tType: [%d -> %s]\n", tmp->elem, tmp->token,
			ft_get_name_type(tmp->token));
        tmp = tmp->next;
    }
	ft_printf("\n---------------------------------\n\n");
}