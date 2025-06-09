#include "../../includes/minishell.h"

int	ft_export(t_mshell *mshell)
{
	if (!mshell->list_cmd->cmd[1])
		ft_print_sorted_env(mshell->env_list);
	else
		ft_edit_var_env(mshell);
	return (0);
}