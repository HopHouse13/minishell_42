/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:12 by pab               #+#    #+#             */
/*   Updated: 2025/06/09 20:18:10 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_mshell *mshell)
{
    char    *home;
 	t_cmd	*cmd_node;
	
	cmd_node = mshell->list_cmd;
    if (!cmd_node->cmd[1] || ft_strcmp(cmd_node->cmd[1], "~") == 0) // si 0 args "cd"
    {
        home = ft_found_value_key(mshell, "HOME");
        if (!home || chdir(home) == -1)
        {
            perror("cd: HOME absent\n");
            return (1);
        }
    }
    else
    {
        if (chdir(cmd_node->cmd[1]) == -1)
        {
            perror("cd");
            return (1);
        }
    }

	//ft_update_env(mshell, cmd_node->cmd[1]);
	//update env / pwd a faire !
    return (0);
}
//update _ pour CMD

// ~
// .
// ..
// cd -
// cd path ok




