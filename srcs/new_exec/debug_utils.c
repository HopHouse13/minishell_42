/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:38:01 by phautena          #+#    #+#             */
/*   Updated: 2025/06/10 15:56:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd(t_mshell *mshell)
{
	int	i;
	t_cmd	*current;

	current = mshell->list_cmd;
	while (current)
	{
		printf("CMD: ");
		i = 0;
		while (current->cmd[i])
		{
			printf("[%s] ", current->cmd[i]);
			i++;
		}
		printf("\nPATH: [%s]]\n", current->path);
		printf("Builtin: %d\n", current->builtin);
		if (current->no_cmd == true)
			printf("no_cmd --> YES\n");
		printf("FDIN / FDOUT / FDHD: [%d] [%d] [%d]\n", current->fd_in, current->fd_out, current->fd_hd);
		if (current->delim_hd != NULL)
			printf("HEREDOC LIM: [%s]\n", current->delim_hd);
		printf("--------------------------------------------\n");
		current = current->next;
	}
}
