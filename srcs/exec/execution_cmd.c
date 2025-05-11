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
	(void)envp;
	int token;

	token = mshell->list_token->token;

	ft_build_path(mshell);
	//ft_redir(mshell);

	if (mshell->count_pipe)
	{
		printf(CYAN "\n[INFO]Bonne detection du pipe ; Entree dans ft_piper" RESET"\n");
		ft_piper(mshell);
	}
	else if (token == CMD && !mshell->count_pipe)
	{
		printf(CYAN "\n[INFO]Commande basique :"RESET YELLOW"%s"RESET"\n",mshell->list_cmd->cmd[0]);
		ft_forker(mshell);
		//ft_forker_test(mshell); // no pipe
	}
	if (token == BI)
	{
		ft_exe_built_in(mshell);
	}
	if (token == HD)
	{
		printf("HereDoc par la\n");
	}
	//redirect(mshell); // dans le parent ou dans l'enfant ?
	printf(RED "\n[INFO]fin de l'exec."RESET"\n");
}

void	ft_build_path(t_mshell *mshell)
{
	char **cmd;
	cmd = mshell->list_cmd->cmd;

	if (ft_ispath(cmd[0]))
		return ;
	else
		ft_build_cmd_path(mshell);
	return ;
}

void	ft_build_cmd_path(t_mshell *mshell)
{
	char	*path_env;
	char	**path_tab;	

	//1)a) //Recuperer le contenu PATH depuis liste chainee {key:value} (char *)
	path_env = ft_strdup(ft_get_env("PATH", mshell->env_list));

	//1)b) + --> "split" les path -- passer directement sur du char ** depuis char **?
	path_tab = ft_split(path_env, ':');
	//printf_tab(path_tab);

	//2) //Adjoindre avec la commande
	ft_path_makeur(mshell, path_tab);

	free(path_env);
	ft_free_tab(path_tab);
	//if (ft_check_path_access(path_clean))
	//	return ;

}

void	ft_path_makeur(t_mshell *mshell, char **path_tab)
{
	int		i;
	char	*temp;
	char	*path_join;
	char	**cmd;

	cmd = mshell->list_cmd->cmd;
	i = 0;
	while (path_tab[i])
	{
		//creation du path
		temp = ft_strjoin(path_tab[i], "/"); //what seg fault si env -i ?
		path_join = ft_strjoin(temp, cmd[0]);
		free(temp);
		if(!path_join)
		{
			free(path_join);
			perror("Path_join failed to ft_strjoin");
			return ;
		}
		if (access(path_join, F_OK | X_OK) == 0) //test + ajout a la liste chainee
		{
			free(cmd[0]);
			cmd[0] = ft_strdup(path_join);
			free(path_join);
			break;
		}
		free(path_join);
		i++;
	}
	return ;
}



void	printf_tab(char **str)
{
	int	i = 0;

	while (str[i])
	{
		printf("%s \t",str[i]);
		i++;
	}
}

/*
char	**get_binpath_brut(char **envp)
{
	char	*env_path;
	char	**bin_path;
	int		i;

	env_path = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp (envp[i], "PATH=", 5))
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (env_path == NULL)
		return (NULL);
	bin_path = ft_split (env_path, ':');
	return (bin_path);
}
*/


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