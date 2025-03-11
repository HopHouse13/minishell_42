#include "minishell.h"

void    redirect(src((fd)), dest((sens?)))
{
    /*
        Open un fd (open);
        change les fd de rediction I/O (dup2) ; 2 cas :
            - Redirecition Input
            - Redirection Output
        referme proprement(close)
     */
    
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

void    redirect_case(fd, tokken)
{
    if (tokken == "<")
        redirect_in (src,dest);
    else if (tokken == ">")
        redirect_out_trunc (src, dest);
    else if (tokken == ">>")
        redirect_out_app (src,dest);
    else if (tokken == "<<")
        redirect_hd (src, dest); 

}

void    redirect_in(, char *infile)
{
    //dup2
    int fd_open;

    fd_open = open (infile, O_RDONLY);
    if (fd_open == -1)
    {
        perror ("Pas pu ouvrir le fichier : ");
        exit (1);
    }
    dup2 (fd_open, fd);
    close (fd_open);
    return :
}


void    redirect_out_trunc(src,dest)
{



}

void    redirect_out_app(src,dest)
{



}

void    redirect_hd(src, dest)
{




}