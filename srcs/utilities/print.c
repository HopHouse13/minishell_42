/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:13:42 by pab               #+#    #+#             */
/*   Updated: 2025/05/09 17:34:18 by pab              ###   ########.fr       */
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

char	*ft_get_name_type(t_type type)
{
	char *type_tab[] = { "ELEM", "PIPE", "R_IN", "R_OUT", "HD",
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

void	ft_print_list_cmd(t_mshell *mshell) // A SUPP
{
    t_cmd	*tmp;
	int		counter;
	
	counter = 1;
	tmp = mshell->list_cmd;
	if (tmp)
	{
		ft_printf("\n\t******************* list_cmd *********************\n\n");
    	while (tmp != NULL)
    	{
			printf("\n\t\t\t--- NODE Nº %d ---\n\n", counter++);
			ft_print_double_tab(tmp->cmd);
			printf("\t\tFD_INFILE\t->\t[%d]\n", tmp->fd_in);
			printf("\t\tFD_OUTFILE\t->\t[%d]\n", tmp->fd_out);
			printf("\t\tFD_HD\t\t->\t[%d]\n", tmp->fd_hd);
			printf("\t\tDELIM_HD\t->\t[%s]\n", tmp->delim_hd);
			printf("\t\tEXPAND_HD?\t->\t[%d]\n", tmp->expand_hd);
    	    tmp = tmp->next;
    	}
		printf("\n\n\t\tNOMBRE_DE_PIPE\t->\t[%d]\n\n",mshell->count_pipe);
	}
}
