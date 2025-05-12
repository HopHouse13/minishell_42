#include "../../includes/minishell.h" 

/*
int ft_piper(t_mshell *mshell, char **envp)
{
	pid_t   pid;
	t_cmd   *cmd;
	int		pipe_fd[2];
	int		prev_fd;

	cmd = mshell->list_cmd;
	prev_fd = -1;
    //pid_t   pid2;
    //int     status;

    // prendre une fonction et la rendre agnostique pour pouvoir rediriger constement le 'in' et le 'out'
    while (cmd)
    {
		mshell->count_pipe;
        if (cmd->next && pipe(pipe_fd) == -1)
        {
            perror("Probleme pipe");
            exit(1);
        }
		pid = fork(); // ofrk
        if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		if (pid == 0)
		{
			
			if (prev_fd != -1) //redir IN si 2eme com. // init a -1
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next)  //redir sortie
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			if (prev_fd != -1)
			{
				ft_redir_pipe(mshell);
			}
				// avec access ; code 127 'command not found'
			if (execve (cmd->cmd[0], cmd->cmd, envp) == -1)
			{
				perror ("Execve 1");
				exit (127); // commande found bcleaut not executable
			}
		}
		mshell->count_pipe--;
		printf("[INFO] Pipe Count : %i\n", mshell->count_pipe);
		if (prev_fd != -1) // si on est sur cmd[1+]
			close(prev_fd); // ferme lecture
		if (cmd->next) // si yq une cmd qui suit
			close(pipe_fd[1]); //ferme l'ecriture

		if (cmd->next != NULL) //si ya une commande suivante
			prev_fd = pipe_fd[0];
		else
			prev_fd = -1;
		// comment recuperer l'exit_code du processus enfant = waitpid() ?
		//waitpid(pid1, &status, 0);
		cmd = cmd->next;
	}

	while (wait(NULL) > 0)
		;
	//wait(NULL);
	//wait(NULL);
	//wait(NULL);

	// ---- inspi GPT ----
	// Récupère le code du dernier
	if (WIFEXITED(status))
		mshell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mshell->exit_status = 128 + WTERMSIG(status);
	
	return (0);
}
*/
int ft_piper(t_mshell *mshell, char **envp)
{
	pid_t   pid;
	t_cmd   *cmd_node;
	int		pipe_fd[2];
	int		prev_fd;

	cmd_node = mshell->list_cmd;
	prev_fd = -1;
    //pid_t   pid2;
    //int     status;

	// mshell->count_pipe;
	//ft_check_path_access(cmd[0]);_
    // prendre une fonction et la rendre agnostique pour pouvoir rediriger constement le 'in' et le 'out'
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
			//si prev == -1 --> fd_in = stdin;


			//ft_pipe_write(mshell, pipe_fd[1]); // redirection OUT actuelle==> P_W
			//ft_pipe_read(mshell, pipe_fd[0]); // redirection IN next cmd ==> P_L
			
			// if (prev_fd != -1) // sous entendu fd next
			// {
			// 	//ft_redir_pipe(mshell, pipe_fd);
			// }
			// avec access ; code 127 'command not found'
			
			//cmd->fd_in = pipe_fd[0];

			/*
			if (prev_fd != -1)
				ft_redir_in(mshell);

			//cmd->fd_out = pipe_fd[1];
			if (cmd->next)
			{
				//close (pipe_fd[0]);
				dup2 (pipe_fd[1], STDOUT_FILENO);
				close (pipe_fd[1]);
			}

			*/
				//ft_redir_pipe_write(mshell, pipe_fd);
				//ft_redir_out(mshell);

			//DEBUG -- PRINT
			printf(CYAN "\n[INFO] Commande en cours : "RESET);
			int i = 0;
			while(cmd_node->cmd[i])
			{
				printf(YELLOW" %s"RESET, cmd_node->cmd[i]);
				i++;
			}
			printf("\n");
			// printf("commande en cours : %s",cmd->cmd[0]);
			if (execve (cmd_node->cmd[0], cmd_node->cmd, envp) == -1)
			{
				perror ("Execve 1");
				exit (127); // commande found bcleaut not executable
			}
		}
		mshell->count_pipe--;
		printf("[INFO] Pipe Count : %i\n", mshell->count_pipe);
		if (prev_fd != -1)     // si on est sur cmd[1+]
			close(prev_fd);    // ferme lecture
		if (cmd_node->next)         // si yq une cmd qui suit
		{
			close(pipe_fd[1]); //ferme l'ecriture
			prev_fd = pipe_fd[0];
		}
		else
			prev_fd = -1;
		// comment recuperer l'exit_code du processus enfant = waitpid() ?
		cmd_node = cmd_node->next;
	}

	while (wait(NULL) > 0)
		;
	return (0);
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
			printf(CYAN "\n[INFO] Commande en cours : "RESET);
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