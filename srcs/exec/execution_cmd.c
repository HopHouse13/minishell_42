#include "../../includes/minishell.h"

/**                         EXEC MINISHELL
    STEP : 
        1/ FORK
        2/ REDIRIGE les fichiers——— (IN,OUT, PIPE)
        3/ TRANSFORME & EXECUTE la cmd
*/

/* ft_executer
    
    - check si BI 
    - - check si heredoc --> surperflu déjà dans parsing ?
    - Si << trouvé :
        lire le contenu (readline)
        créer un pipe temporaire
        écrire dedans
        rediriger stdin de la commande vers le read-end du pipe
    
    - check pipe
    - - créer n-1 pipe
    - - redirections entrées/sorties selon pipe précédent-suivant
    - - fork 
    - - fermeture des piping

    - execution cmd
*/

void	ft_executer(t_mshell *mshell, char **envp, t_mnode **ml)
{
	int 	token;
	t_cmd	*list_cmd;
	// printf(RED"On entre dans l'exe ?"RESET"\n");
	token = mshell->list_token->token;
	list_cmd = mshell->list_cmd;
	while (list_cmd)
	{
		ft_build_path(list_cmd, mshell->env_list, ml);
		list_cmd = list_cmd->next;
	}
	if (mshell->count_pipe)
	{
		printf(CYAN "\n[INFO] Activation Pipeline" RESET"\n");
		ft_piper(mshell, envp);
	}
	else if (list_cmd->cmd && !mshell->count_pipe)
	{
		printf(CYAN "\n[INFO] Commande unique :"RESET YELLOW" %s"RESET"\n", list_cmd->cmd[0]);
		ft_forker(mshell, envp);
	}
	if (token == BI)
	{
		ft_exe_built_in(mshell);
	}
	if (token == HD)
	{
		printf("HereDoc par la\n");
	}
	//wait(NULL);
	printf(RED "\n[INFO] Fin Exec."RESET"\n");
}





// _________ _________________________ ________________________ _________ __ //
/*
    FORK
    REDIRECTION
    EXECUTION 
*/

/*
void    ft_redirect(t_mshell mshell)
{
    // Redirection d'entrée
        if (infile != -1) // indicateur de redirection
        {
            dup2(infile, STDIN_FILENO); // NEED fichier & mode 
            close(infile);
        }
        // Redirection de sortie
        if (mshell->token == REDIR_OUT_Q || mshell->token == APPEND) // indicateur de redirection
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
}*/