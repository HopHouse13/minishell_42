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

void	ft_executer(t_mshell *mshell, char **envp)
{
	t_cmd	*list_cmd;
	
	list_cmd = mshell->list_cmd;
 	if (list_cmd->builtin)
 	{
		printf (CYAN "\n [INFO] Commande BuiltIn :"RESET YELLOW " %s"RESET"\n", list_cmd->cmd[0]);
		ft_exe_built_in(mshell);
	}
	ft_build_path(mshell);
	if (mshell->count_pipe)
	{
		printf(CYAN "\n[INFO] Activation Pipeline" RESET"\n");
		ft_piper(mshell, envp);
	}
	else if (list_cmd->cmd && !mshell->count_pipe && !list_cmd->builtin) 
	{
		printf("\n"CYAN"[INFO] Commande unique :"RESET YELLOW" %s"RESET, list_cmd->cmd[0]);
		ft_forker(mshell, envp);
	}
	if (list_cmd->fd_hd != -1)
	{
		printf("HereDoc par la\n");
	}
	//wait(NULL);
	printf(RED "\n[INFO] Fin Exec."RESET"\n");
}