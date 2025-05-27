#include "../../includes/minishell.h" 

int	ft_exit(t_cmd *cmd)
{
	// La fonction exit() termine le processus du shell de manière contrôlée,
	// en libérant toutes les ressources 
	// et en signalant au système d'exploitation son statut de terminaison.
	int	status;

	printf("exit");
	if (cmd->cmd[1] && !ft_isdigit(ft_atoi(cmd->cmd[1])))
	{
		printf("ft_exit: %s: numeric argument required\n", cmd->cmd[1]);
		exit(1);
	}
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		perror("ft_exit: too many arguments\n");
		return (1);
	}
	if (cmd->cmd[1])
		status = ft_atoi(cmd->cmd[1]) % 256;
	else
		status = 0;
	exit(status);
}
