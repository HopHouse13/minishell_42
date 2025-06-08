/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:27:43 by pab               #+#    #+#             */
/*   Updated: 2025/06/08 16:49:41 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executer(t_mshell *mshell, char **envp)
{
	t_cmd	*list_cmd;
	
	list_cmd = mshell->list_cmd;
	if (list_cmd->builtin)
	{
		printf (CYAN "\n [INFO] Commande BuiltIn :"RESET YELLOW " %s"RESET"\n", list_cmd->cmd[0]);
		ft_exe_built_in(mshell);
	}
	ft_build_path(mshell);
	if (mshell->count_pipe)
	{
		printf(CYAN "\n[INFO] Activation Pipeline" RESET"\n");
		printf("BUG ICI XXX");

		ft_piper(mshell, envp);
		printf("BUG ICI 000");

	}
	else if (list_cmd->cmd && !mshell->count_pipe && !list_cmd->builtin) 
	{
		printf("\n"CYAN"[INFO] Commande unique :"RESET YELLOW" %s"RESET, list_cmd->cmd[0]);
		ft_forker(mshell, envp);
	}
	if (list_cmd->fd_hd != -1)
	{
		printf("HereDoc par la\n");
	}
	// update_env_pwd_old_pwd;
	//wait(NULL);
	ft_free_ml(mshell);
	printf(RED "\n[INFO] Fin Exec."RESET"\n");
}