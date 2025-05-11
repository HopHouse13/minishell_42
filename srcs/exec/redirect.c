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

/*
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

void	ft_redir(t_mshell *mshell)
{
	// differencier les redirection selon le cas operateur ou pipe ?
	// redir ft_redir_pipe ?
	ft_redir_case(mshell);

}

void    ft_redir_case(t_mshell *mshell) //(infile,outfile?)
{
	int token;

	token = mshell->list_token->token;
    //if (token == R_IN)
    //    redirect_in (infile);
    if (token == R_OUT)
	{
		printf(MAGENTA"R_OUT detecte"RESET);
        ft_redir_out (mshell);
	}
	//else if (token == ">>")
    //    redirect_out_app (src,dest);
    //else if (token == "<<")
    //    redirect_hd (src, dest);
}

void	ft_redir_out (t_mshell *mshell)
{
	int	fd_out;

	fd_out = mshell->list_cmd->fd_out;
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

/*
void    redirect_in(, char *infile)
{
    
    Open un fd (open);
    change les fd de rediction I/O (dup2) ; 2 cas :
        - Redirection Input
        - Redirection Output
    referme proprement(close)
    
    int fd_open;

    fd_open = open (infile, O_RDONLY);
    if (fd_open == -1)
    {
        perror ("Pas pu ouvrir le fichier : ");
        exit (1);
    }
    dup2 (fd_open, fd);
    close (fd_open);
    return ;
}
*/