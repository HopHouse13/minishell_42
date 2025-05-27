#include "../../includes/minishell.h" 

/* v1
int ft_piper(t_mshell *mshell, char **envp)
{
	pid_t   pid;
	t_cmd   *cmd_node;
	int		pipe_fd[2];

	cmd_node = mshell->list_cmd;
    while (cmd_node)
    {
        if (cmd_node->next && pipe(pipe_fd) == -1)
        {
            perror("Probleme pipe");
            exit(1);
        }
		pid = fork(); // fork child ; total fd pipe = x2
        if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		if (pid == 0)
		{
			ft_redir_pipe_write(mshell, pipe_fd); // redirection OUT actuelle==> P_W
			ft_redir_pipe_read(mshell, pipe_fd); // redirection IN next cmd ==> P_L

			//DEBUG -- PRINT
			printf(CYAN "\n[INFO] Commande en cours : "RESET);
			int i = 0;
			while(cmd_node->cmd[i])
			{
				printf(YELLOW" %s"RESET, cmd_node->cmd[i]);
				i++;
			}
			printf("\n");

			if (execve (cmd_node->cmd[0], cmd_node->cmd, envp) == -1)
			{
				perror ("Execve 1");
				exit (127); // commande found bcleaut not executable
			}
		}
		mshell->count_pipe--;
		printf("[INFO] Pipe Count : %i\n", mshell->count_pipe);
		wait(NULL);
		cmd_node = cmd_node->next;
	}

	while (wait(NULL) > 0)
		;
	return (0);
}
*/


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
			//setup_child_signals(); // Réinitialiser les signaux
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
			if(execve(cmd_node->cmd[0], cmd_node->cmd, envp) == -1)
			{
				perror("Execve child \n");
				exit(EXIT_FAILURE);
			}
		}
		else 
			wait(NULL);
		cmd_node = cmd_node->next;
	}
}