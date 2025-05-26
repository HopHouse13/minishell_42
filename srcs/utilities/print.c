/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:13:42 by pab               #+#    #+#             */
/*   Updated: 2025/05/26 20:24:16 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_double_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			printf("\t\tELEM Nº %d\t->\t[ %s ]\n", i, tab[i]);
	}
}

char	*ft_get_name_type(t_type type)
{
	char	*type_tab[14];

	type_tab[0] = "ELEM";
	type_tab[1] = "PIPE";
	type_tab[2] = "R_IN";
	type_tab[3] = "R_OUT";
	type_tab[4] = "HD";
	type_tab[5] = "APPEND";
	type_tab[6] = "F_IN";
	type_tab[7] = "F_OUT";
	type_tab[8] = "F_APP";
	type_tab[9] = "DELIM";
	type_tab[10] = "CMD";
	type_tab[11] = "BI";
	type_tab[12] = "ARG";
	type_tab[13] = "END";
	if (type >= ELEM && type <= END)
		return (type_tab[type]);
	return ("INVALID_TYPE");
}

void	ft_print_list_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (!tmp)
		return ;
	ft_printf("\n\t\t\t*** LIST_ELEMENTS ***\n\n");
	while (tmp)
	{
		printf("\t\tElem [ %s ]\tToken [ %s ]\n\n", tmp->elem,
			ft_get_name_type(tmp->token));
		tmp = tmp->next;
	}
}

void	ft_print_header_list_cmd(void)
{
	printf(CYAN"\t╔═════════════════════════════════════════════════╗\n");
	printf("\t║\t\t\t\t\t\t  ║\n");
	printf(GREEN"\t\t\t   \033[1m[ LIST_CMD ]\n");
	printf(MAGEN"\t║\t\t\t\t\t\t  ║\n");
	printf("\t╚═════════════════════════════════════════════════╝\n%s", RESET);
}

void	ft_print_list_cmd(t_mshell *mshell)
{
	t_cmd	*tmp;
	int		counter;

	counter = 1;
	tmp = mshell->list_cmd;
	if (!tmp)
		return ;
	ft_print_header_list_cmd();
	while (tmp != NULL)
	{
		printf(GREEN"\n\t\t\t\033[1m--- NODE Nº %d ---\n\n", counter++);
		ft_print_double_tab(tmp->cmd);
		printf("\n\t\tBUILTIN?\t->\t[ %d ]\n", tmp->builtin);
		printf("\t\tFD_INFILE\t->\t[ %d ]\n", tmp->fd_in);
		printf("\t\tFD_OUTFILE\t->\t[ %d ]\n", tmp->fd_out);
		printf("\t\tFD_HD\t\t->\t[ %d ]\n", tmp->fd_hd);
		printf("\t\tDELIM_HD\t->\t[ %s ]\n", tmp->delim_hd);
		printf("\t\tEXPAND_HD?\t->\t[ %d ]\n%s", tmp->expand_hd, RESET);
		tmp = tmp->next;
		printf(CYAN"\n\t\t══════════════════════════════════\n");
		printf(MAGEN"\t\t══════════════════════════════════\n%s", RESET);
	}
}
