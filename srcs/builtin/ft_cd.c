/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:12 by pab               #+#    #+#             */
/*   Updated: 2025/06/11 17:27:37 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	update_pwd(t_mshell *mshell, char *old_pwd, char *new_pwd)
// {
// 	ft_env
// }



// int	ft_cd(char **argv, t_mshell *mshell)
// {
// 	int	ret;
// 	char	*path;
// 	char	*old_pwd;
// 	char	*new_pwd;

// 	if (argv[1] && argv[2])
// 		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
// 	if (!argv[1])
// 	{
// 		path = ft_found_value_key(mshell, "HOME");
// 		if (!path)
// 			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
// 	}
// 	else
// 		path = argv[1];
// 	old_pwd = getcwd(NULL, 0);
// 	if (!old_pwd)
// 		return (ft_mem_err(mshell), 0);
// 	ret = chdir(path);
// 	if (ret == -1)
// 		return (perror("minishell: cd"), 1);
// 	new_pwd = getcwd(NULL, 0);
// 	if (!new_pwd)
// 		return (ft_mem_err(mshell), 1);
// 	return ()
// }

