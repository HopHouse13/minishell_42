/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:28:45 by pab               #+#    #+#             */
/*   Updated: 2025/06/12 11:57:15 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//BI_list = {"cd", "echo", "env", "exit", "pwd", "export", "unset"};

// void	ft_exe_built_in(t_mshell *mshell)
// {
// 	char	*cmd;
// 	cmd = mshell->list_cmd->cmd[0];
// 	if (ft_strcmp(cmd, "cd") == 0)
// 	{
// 		printf(CYAN"[INFO] BI : "RESET YELLOW"cd"RESET"\n");
// 		// ft_cd(mshell);
// 	}
// 	else if (ft_strcmp(cmd, "echo") == 0)
// 	{
// 		printf(CYAN"[INFO] BI : "RESET YELLOW"echo"RESET"\n");
// 		ft_echo(mshell);
// 	}
// 	else if (ft_strcmp(cmd, "env") == 0)
// 	{
// 		ft_env(mshell);
// 		printf(CYAN"[INFO] BI : "RESET YELLOW"env"RESET"\n");
// 	}
// 	else if (ft_strcmp(cmd, "exit") == 0)
// 	{
// 		printf(CYAN"[INFO] BI : "RESET YELLOW"exit"RESET"\n");
// 		ft_exit(mshell->list_cmd);
// 	}
// 	else if (ft_strcmp(cmd, "export") == 0)
// 	{
// 		printf(CYAN"[INFO] BI : "RESET YELLOW"export"RESET"\n");
// 		ft_export(mshell);
// 	}
// 	else if (ft_strcmp(cmd, "pwd") == 0)
// 	{
// 		ft_pwd();
// 	}
// 	else if (ft_strcmp(cmd, "unset") == 0)
// 	{
// 		printf(CYAN"[INFO] BI : "RESET YELLOW"unset"RESET"\n");
// 		ft_unset(mshell);
// 	}
// 	return ;
// }
