#include "../../includes/minishell.h" 

/*
void    ft_forker(char **av, int *fd)
{
    // refaire un systeme avec les redirection 
    // detection redirection IN ou OUT 
    // eviter 2 forker first and second
    pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Bruh Fork 1 : ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close (fd[0]);
		dup2 (fd[1], STDIN_FILENO);
		close (fd[1]);
		redirect_arg (av[1], 0, "in"); // merge new redirection
 		transformer (envp, av[2]);
	}
}

void	redirect_arg(char *av_arg, int fd, char *location)
{
	int	fd_open;

	fd_open = 0;
	if (!ft_strncmp (location, "in", 2))
		fd_open = open (av_arg, O_RDONLY);
	else if (!ft_strncmp (location, "out", 3))
		fd_open = open (av_arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_open == -1)
	{
		perror("Bruh acces file : ");
		exit(1);
	}
	dup2 (fd_open, fd);
	close (fd_open);
	return ;
}
*/

int ft_piper(t_mshell *mshell)
{
	t_cmd   *cmd = mshell->list_cmd;
	int pipe_fd[2];
	pid_t   pid1;
	int prev_fd;

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

		pid1 = fork(); // ofrk
        if (pid1 == -1)
		{
			perror("fork failed");
			exit(1);
		}
		if (pid1 == 0)
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
			if (execve (cmd->cmd[0], cmd->cmd, NULL) == -1)
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



void    ft_forker(t_mshell *mshell)
{
    //mshell->env = test_env_init("defaut"); //"defaut" ou "vide" (env -i) 

    pid_t pid;
    
    //   ----- SIMULATION INPUT
    /*
    mshell->list_cmd = cmd_init();
    mshell = cmd_remplissage(mshell);
	*/
    //   ------
    t_cmd *cmd_node = mshell->list_cmd;
    
    while(cmd_node)
    {
        pid = fork();
        if (pid == 0)
        {
            //SECURITE
            if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
            {
                printf("Commande vide !\n");
                exit(EXIT_FAILURE);
            }


            //DEBUG
            printf("Commande en cours : ");
            int i = 0;
            while(cmd_node->cmd[i])
            {
                printf("\033[33m%s \033[0m", cmd_node->cmd[i]);
                i++;
            }
            printf("\n");


            //EXECUTION (manque chemin relatif)
            if(execve(cmd_node->cmd[0], cmd_node->cmd, NULL) == -1)
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