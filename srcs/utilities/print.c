/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:54 by pbret             #+#    #+#             */
/*   Updated: 2025/03/13 15:13:46 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_input_clean(char *line)
{
	ft_printf("\n\t----------- input_clean ----------\n\n");
	ft_printf("\n\tline : [%s]\n\n", line);
}

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
	const char *type_tab[] = { "ELEM", "PIPE", "REDIR_IN", "REDIR_OUT", "HD",
							"END_HD", "APPEND", "DOLLAR", "END", "UNKNOWN"};
	
	if ( type >= ELEM && type <=UNKNOWN)
		return (type_tab[type]);
	return ("INVALID_TYPE");
}

void	ft_print_list_token(t_token *head) // A SUPP
{
    t_token	*tmp;
	
	tmp = head;
	ft_printf("\n\t----------- list_token -----------\n\n");
    while (tmp)
    {
        printf("\tToken: [%s]\t\tType: [%d -> %s]\n\n", tmp->elem, tmp->token,
		ft_get_name_type(tmp->token));
        tmp = tmp->next;
    }
	// ft_printf("\n---------------------------------\n\n\n");
}

void	ft_print_list_cmd(t_cmd *head) // A SUPP
{
    t_cmd	*tmp;
	// char	**tab_cmd;
	
	//tab_cmd = head->cmd;
	tmp = head;
	ft_printf("\n\t----------- list_cmd ------------\n\n");
    while (tmp)
    {
		/* while (*tab_cmd)
        	ft_printf("cmd: [%s]\n", *tab_cmd++); */
		ft_printf("\n\tquote -> %d\n", tmp->dquote);
        tmp = tmp->next;
    }
	// ft_printf("\n---------------------------------\n\n\n");
}	