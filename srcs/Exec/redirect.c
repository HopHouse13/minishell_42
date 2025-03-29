#include "minishell.h"

void    redirect(t_mshell instructions)
{
    //besoin comme info :
       // - nom de fichier (char *)
       // - nom de commande (char *)
       // - - -redirection 
            // - - types (<, >, >>, <<)
            // - - nombre ?
            // - - spe << : delimiter ?


  
    




    /* 
    if (hd)
        redirection_hd()
    else
        redirection_std()
    */
    redirect_case(fd, tokken)
    //int fd_open;
    //open (av_arg, 0_RDONLY); open (av_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    //dup2(fd_open, fd);
    //close



}

void    redirect_case(fd, tokken) //(infile,outfile?)
{
    if (tokken == "<")
        redirect_in (infile);
    else if (tokken == ">")
        redirect_out_trunc (outfile);
    else if (tokken == ">>")
        redirect_out_app (src,dest);
    else if (tokken == "<<")
        redirect_hd (src, dest); 

}

void    redirect_in(, char *infile)
{
     /*
        Open un fd (open);
        change les fd de rediction I/O (dup2) ; 2 cas :
            - Redirecition Input
            - Redirection Output
        referme proprement(close)
    */
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

void    redirect_out_trunc(char *outfile)
{
    int fd_open;

    fd_open = open (outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_open == -1)
    {
        perror ("Pas pu ouvrir le fichier : ");
        exit (1);
    }
    dup2 (fd_open, fd);
    close (fd_open);
    return ;

}

void    redirect_out_app(char *outfile)
{
     int fd_open;

    fd_open = open (outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_open == -1)
    {
        perror ("Pas pu ouvrir le fichier : ");
        exit (1);
    }
    dup2 (fd_open, fd);
    close (fd_open);
    return ;

}

void    redirect_hd(src, dest)
{
    int fd_open;
    
    //heredoc comportement ici,
    //redirection input cmd depuis file tempo 
    //revoir les regles de prio & delimiter
    fd_open


}