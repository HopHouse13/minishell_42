/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:54 by pbret             #+#    #+#             */
/*   Updated: 2025/04/22 19:36:01 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_input_clean(char *line)
{
	ft_printf("\n\t******************** input_clear *********************\n\n");
	ft_printf("\tline : [%s]\n\n", line);
}

void	ft_print_double_tab(char **tab)
{
	int	i;

	i = -1;
	if(tab)
	{
		while (tab[++i])
			printf("\t\tELEM Nº %d\t->\t%s\n", i, tab[i]);
	}
}

const char	*ft_get_name_type(t_type type)
{
	const char *type_tab[] = { "ELEM", "PIPE", "R_IN", "R_OUT", "HD",
								"APPEND", "F_IN", "F_OUT", "F_APP",
								"DELIM", "CMD", "BI", "ARG", "END"};
	
	if ( type >= ELEM && type <=END)
		return (type_tab[type]);
	return ("INVALID_TYPE");
}

void	ft_print_list_token(t_token *head) // A SUPP
{
    t_token	*tmp;
	
	tmp = head;
	if (tmp)
	{
		ft_printf("\n\n\t\t\t --- list_token --- \n\n");
    	while (tmp)
    	{
    	    printf("\tToken: [%s]\t\tType: [%s]\n\n", tmp->elem,
			ft_get_name_type(tmp->token));
    	    tmp = tmp->next;
    	}
	}
}

void	ft_print_list_cmd(t_cmd *head) // A SUPP
{
    t_cmd	*tmp;
	int		counter;
	
	counter = 1;
	tmp = head;
	if (tmp)
	{
		ft_printf("\n\t******************* list_cmd *********************\n\n");
    	while (tmp != NULL)
    	{
			printf("\n\t\t\t--- NODE Nº %d ---\n\n", counter++);
			ft_print_double_tab(tmp->cmd);
			printf("\t\tINFILE\t\t->\t[%d]\n", tmp->infile);
			printf("\t\tOUTFILE\t\t->\t[%d]\n", tmp->outfile);
			printf("\t\tFD_HD\t\t->\t[%d]\n", tmp->fd_hd);
			printf("\t\tDELIM_HD\t->\t[%s]\n", tmp->delim_hd);
    	    tmp = tmp->next;
    	}
	}
}
