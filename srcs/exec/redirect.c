#include "../../includes/minishell.h"

	/*
	void    redirect(t_mshell instructions)
	{
		//besoin comme info :
		// - nom de fichier (char *)
		// - nom de commande (char *)
		// - - -redirection 
				// - - types (<, >, >>, <<)
				// - - nombre ?
				// - - spe << : delimiter ?
		
		if (hd)
			redirection_hd()
		else
			redirection_std()
		
		redirect_case(fd, tokken)
		//int fd_open;
		//open (av_arg, 0_RDONLY); open (av_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		//dup2(fd_open, fd);
		//close
	}
	*/

void	ft_redir(t_mshell *mshell)
{
	// differencier les redirection selon le cas operateur ou pipe ?
	//ft_redir_case(mshell);
	t_cmd *redir;

	redir = mshell->list_cmd;
	if (redir->fd_out != -1)
	{
		printf(MAGENTA"[INFO] Redirection OUT"RESET"\n");
		ft_redir_out (mshell);
	}
	if (redir->fd_in != -1)
	{
		printf(MAGENTA"[INFO] Redirection IN"RESET"\n");
		ft_redir_in (mshell);
	}
	return ;
	/*
	if (redir->fd_hd != -1)
	{
		printf(MAGENTA"[INFO] FD_HD detectee"RESET"\n");
		ft_redir_hd(mshell);
	}
	*/
}
/*
void    ft_redir_case(t_mshell *mshell) //(infile,outfile?)
{

}
*/

void	ft_redir_out (t_mshell *mshell)
{
	int	fd_out;

	fd_out = mshell->list_cmd->fd_out;
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	ft_redir_in(t_mshell *mshell)
{
	int	fd_in;

	fd_in = mshell->list_cmd->fd_in;
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

/* void	ft_redir_hd(t_mshell *mshell)
{

}
*/

/*
void	ft_redir_pipe(t_mshell *mshell, int *pipe_fd)
{
	t_cmd *redir;

	redir = mshell->list_cmd;
	if (redir->fd_in != -1)
	{
		ft_pipe_read (mshell, pipe_fd[0]); //redir. stdin --> P_L
	}
	if (redir->fd_out != -1)
	{
		ft_pipe_write (mshell, pipe_fd[1]); //redir. stdout --> P_W
	}
	return ;
}
*/

void	ft_redir_pipe(t_mshell *mshell, int *pipe_fd)
{
	ft_pipe_read (mshell, pipe_fd[0]); //redir. stdin --> P_L
	ft_pipe_write (mshell, pipe_fd[1]); //redir. stdout --> P_W
}

void	ft_pipe_read(t_mshell *mshell, int pipe_read) // redir stdout --> P_W
{
	int	fd_in;
	
	printf(MAGENTA"[INFO] Redirection IN"RESET"\n");
	fd_in = mshell->list_cmd->fd_in;
	if (fd_in == -1)
		fd_in = STDIN_FILENO;
	dup2 (pipe_read, fd_in);
	close (pipe_read);
}

void	ft_pipe_write(t_mshell *mshell, int pipe_write) //redir. stdIN --> P_L
{
	int	fd_out;
	
	printf(MAGENTA"[INFO] Redirection OUT"RESET"\n");
	fd_out = mshell->list_cmd->fd_out;
	if (fd_out == -1)
		fd_out = STDOUT_FILENO;
	dup2 (pipe_write, fd_out);
	close (pipe_write);
}
