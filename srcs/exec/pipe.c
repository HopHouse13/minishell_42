#include "../../includes/minishell.h" 



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
			// avec access ; code 127 'command not found'
			if (execve (cmd->cmd[0], cmd->cmd, envp) == -1)
			{
				perror ("Execve 1");
				exit (127); // commande found bcleaut not executable
			}
		}

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

	/* ---- inspi GPT ----
	// Récupère le code du dernier
	if (WIFEXITED(status))
		mshell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mshell->exit_status = 128 + WTERMSIG(status);
	*/
	return (0);
}

void    ft_forker(t_mshell *mshell, char **envp)
{
    //mshell->env = test_env_init("defaut"); //"defaut" ou "vide" (env -i) 
    pid_t	pid;
    t_cmd	*cmd_node = mshell->list_cmd;
	
	while(cmd_node)
    {


        pid = fork();
        if (pid == 0)
        {

			if (cmd_node->fd_out != -1)
			{
				ft_redir(mshell); 
				printf(MAGENTA"Redirection terminee ; passage dans ft_executer"RESET);
			}
            //SECURITE
            if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
            {
                printf("Commande vide !\n");
                exit(EXIT_FAILURE);
            }
            //DEBUG
            printf(CYAN "\n[INFO] Commande en cours : "RESET);
            int i = 0;
            while(cmd_node->cmd[i])
            {
                printf(YELLOW" %s"RESET, cmd_node->cmd[i]);
                i++;
            }
            printf("\n");
            //EXECUTION
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