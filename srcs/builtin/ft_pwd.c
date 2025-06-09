#include "../../includes/minishell.h"

int	ft_pwd(t_mshell *mshell)
{
	(void)mshell;
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	//ft_strdup_ml(mshell, ft_get_env_value(mshell, "PWD")); // printf + boucle
    /* if (!pwd)
    {
        perror("PWD = NULL\n");
		exit (1);
    }
    else */
    return (printf("%s", pwd));

		// .
		// ..



}
