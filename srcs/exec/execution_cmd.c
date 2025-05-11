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


void    ft_executer(t_mshell *mshell, char **envp)
{
	int token;

	token = mshell->list_token->token;

	ft_build_path(mshell, envp);
	//ft_redir(mshell);

	if (mshell->count_pipe)
	{
		printf(CYAN "[INFO]Bonne detection du pipe ; Entree dans ft_piper" RESET"\n");
		ft_piper(mshell);
	}
	else if (token == CMD && !mshell->count_pipe)
	{
		printf(CYAN "[INFO]Commande basique :"RESET YELLOW"%s"RESET"\n",mshell->list_cmd->cmd[0]);
		ft_forker(mshell);
		//ft_forker_test(mshell); // no pipe
	}
	if (token == BI)0
	{
		ft_exe_built_in(mshell);
	}
	if (token == HD)
	{
		printf("HereDoc par la\n");
	}
	//redirect(mshell); // dans le parent ou dans l'enfant ?
	printf(RED "[INFO]fin de l'exec."RESET"\n");
}

void	ft_build_path(t_mshell *mshell, char **envp)
{
	char **cmd;
	cmd = mshell->list_cmd->cmd;

	if (ft_ispath(cmd[0]))
		return ;
	else
		ft_build_cmd_path(mshell, envp);
	return ;
}

void	ft_build_cmd_path(t_mshell *mshell, char **envp)
{
	char	*path_clean;
	t_cmd	*cmd;

	cmd = mshell->list_cmd;

	path_clean = ft_pathifier(cmd->cmd[0], envp);
	if (!path_clean)
		exit (126);

	cmd->cmd[0] = path_clean;

	// cmd -> parse format ->test 

}


char *ft_pathifier(char *cmd, char **envp)
{
	int	i;
	char **path_envp;
	char *path_clean;
	char cmd_path;
	//1)a) //Recuperer le contenu de PATH (char *)
	path_clean = strdup (path_envp[ii]);
	//1)b) + --> "split" les path -- passer directement sur du char ** depuis char **?
	path_envp = ft_split(path_clean, ":");


	//2) //Adjoindre avec la commande
	i = 0;
	while (path_envp[i])
	{
		path_clean = ft_strjoin(path_envp[i], cmd);
		//3) //Tester chaque path
		if (ft_check_path_access(path_clean))
			return (cmd_path);
		i++;
	}
	

	return (NULL);
}



// _________ _________________________ ________________________ _________ __ //
/*
    FORK
    REDIRECTION
    EXECUTION 
*/

/*
void    ft_forker_test(t_mshell *mshell)
{
    //mshell->env = test_env_init("defaut"); //"defaut" ou "vide" (env -i) 

    pid_t pid;
    
    //   ----- SIMULATION INPUT
    
    mshell->list_cmd = cmd_init();
    mshell = cmd_remplissage(mshell);

    //   ------
    t_cmd *cmd_node = mshell->list_cmd->next;
    
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
