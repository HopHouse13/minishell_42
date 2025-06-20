/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:14:37 by pab               #+#    #+#             */
/*   Updated: 2025/06/20 13:54:02 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long long	ft_atoll_exit(const char *str, int *error)
{
	int			i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if ((str[0] != '+' && sign == 1 && i == 18 && str[i] > '7') || (i == 19
				&& sign == -1 && str[i] == '9') || (str[0] == '+' && sign == 1
				&& i == 19 && str[i] > '7'))
			*error = 1;
		i++;
	}
	if (str[i] || (str[0] != '+' && i > 19 && sign == 1) || (str[0] == '+'
			&& i > 20 && sign == 1) || (i > 20 && (sign == -1)))
		*error = 1;
	return (result * sign);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit_error(char *current, int has_next)
{
	int	error;

	if (!ft_isnumber(current))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(current, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (has_next)
	{
		return (printf("exit\n"),
			ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	}
	error = 0;
	ft_atoll_exit(current, &error);
	if (error == 1)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(current, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	return (0);
}

void	close_dup(int save, int save2)
{
	dup2(save, STDIN_FILENO);
	dup2(save, STDOUT_FILENO);
	close(save);
	close(save2);
}

int	ft_exit(char **argv, t_mshell *mshell, int save, int save2)
{
	unsigned int	exit_code;

	if (!argv[1])
	{
		printf("exit\n");
		close_dup(save, save2);
		free_mshell(mshell);
		exit(0);
	}
	if (ft_exit_error(argv[1], argv[2] != NULL))
		return (1);
	exit_code = ft_atoll_exit(argv[1], NULL);
	if (exit_code > 255)
		exit_code %= 256;
	printf("exit\n");
	close_dup(save, save2);
	free_mshell(mshell);
	exit(exit_code);
	return (0);
}

// int	ft_exit(t_cmd *cmd)
// {
// 	// La fonction exit() termine le processus du shell de manière contrôlée,
// 	// en libérant toutes les ressources
// 	int	status;

// 	printf("exit");
// 	if (cmd->cmd[1] && !ft_isdigit(ft_atoi(cmd->cmd[1])))
// 	{
// 		printf("ft_exit: %s: numeric argument required\n", cmd->cmd[1]);
// 		exit(1);
// 	}
// 	if (cmd->cmd[1] && cmd->cmd[2])
// 	{
// 		perror("ft_exit: too many arguments\n");
// 		return (1);
// 	}
// 	if (cmd->cmd[1])
// 		status = ft_atoi(cmd->cmd[1]) % 256;
// 	else
// 		status = 0;
// 	exit(status);
// }
