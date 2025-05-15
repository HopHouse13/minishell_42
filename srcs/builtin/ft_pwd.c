#include "../../includes/minishell.h"

int	ft_pwd(t_mshell *mshell, t_mnode **ml)
{
	char	*pwd;

	pwd = ft_strdup_ml(get_value(mshell, "PWD"), ml);
    if (!pwd)
    {
        perror("PWD = NULL\n");
		exit (1);
    }
    else
        return (printf("%s", pwd));
}
