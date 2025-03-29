#include "../../includes/minishell.h"

void    redirect(void)
{

    
    //besoin comme info :
       // - nom de fichier (char *)
       // - nom de commande (char *)
       // - - -redirection 
            // - - types (<, >, >>, <<)
            // - - nombre ?
            // - - spe << : delimiter ?

    char *infile = "tust.txt";

    redirect_in(infile);

        
    /* 
    if (hd)
        redirection_hd()
    else
        redirection_std()
    */
    //redirect_case(fd, tokken)s
    //int fd_open;
    //open (av_arg, 0_RDONLY); open (av_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    //dup2(fd_open, fd);
    //close



}
/***
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
*/
void    redirect_in(char *infile)
{
     /*
        si fichier existe, Open un fd (open);
        si non erreur et pas de creation de fichier;
        change les fd de rediction I/O (dup2) ; 2 cas :
            - Redirection Input
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
    if (dup2 (fd_open, STDIN_FILENO) == -1)
    {
        perror("erreur redirection entree");
        close(fd_open);
        exit(EXIT_FAILURE);
    }
    
    if (close(fd_open) == -1)
    {
        perror("Erreur lors de la fermeture du fichier");
        exit(EXIT_FAILURE);
    }   
    
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
    dup2 (fd_open, STDOUT_FILENO);
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
    dup2 (fd_open, STDOUT_FILENO);
    close (fd_open);
    return ;

}

void    redirect_hd(char *infile)
{
    int fd_open;
    
    //heredoc comportement ici,
    //redirection input cmd depuis file tempo 
    //revoir les regles de prio & delimiter
    //fd_open


}