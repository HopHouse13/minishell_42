/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:56:05 by pab               #+#    #+#             */
/*   Updated: 2025/05/27 16:53:19 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

// v3
int ft_piper(t_mshell *mshell, char **envp)
{
	t_cmd *cmd = mshell->list_cmd;
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;

	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) // child
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next)
			{
				close(pipe_fd[0]); // close unused read end
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			// signal + maj '_'
			execve(cmd->cmd[0], cmd->cmd, envp);
			perror("execve");
			exit(127);
		}

		// parent
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			prev_fd = -1;

		cmd = cmd->next;
	}

	while (wait(NULL) > 0);
	return 0;
}

//prevoir que si les pipes fail , on close les fd ouverts ??

void	ft_forker(t_mshell *mshell, char **envp)
{
	//mshell->env = test_env_init("defaut"); //"defaut" ou "vide" (env -i) 
	pid_t	pid;
	t_cmd	*cmd_node = mshell->list_cmd;

	//ft_check_path_access(list->cmd[0])
	while(cmd_node)
	{
		pid = fork();
		if (pid == 0)
		{
			//SECURITE
			if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
			{
				printf(RED"Commande vide !"RESET"\n");
				exit(EXIT_FAILURE);
			}
			//DEBUG -- PRINT
			printf(CYAN "\n[INFO] Commande en cours : "RESET"");
			int i = 0;
			while(cmd_node->cmd[i])
			{
				printf(YELLOW" %s"RESET, cmd_node->cmd[i]);
				i++;
			}
			printf("\n");
			//EXECUTION
			ft_redir(mshell);
			ft_child_signals();
			if(execve(cmd_node->cmd[0], cmd_node->cmd, envp) == -1)
			{
				perror("Execve child \n");
				ft_free_ml(mshell);
				ft_free_env(mshell->env_list);
				free((*mshell).qts);
				free(mshell);
				exit(127);
			}
		}
		else 
			wait(NULL);
		cmd_node = cmd_node->next;
	}
}