#include "../../includes/minishell.h" 

/*
void    pipe(void)
{
    int fd_entry; // arguments ??
    int fd_exit; // argmument ?? 

    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("error pipe ");
        exit(EXIT_FAILURE);
    }
    //fork_entry;
    //fork_exit;
    // établir strategie / lien avec redirect()  
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
}

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