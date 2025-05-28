/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:50 by pbret             #+#    #+#             */
/*   Updated: 2025/05/28 14:29:49 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_build_err_mess(t_mshell *ms, char *message, char *elem)
{
	char	*mess;

	mess = NULL;
	mess = ft_strjoin_ml(ms, "minishell: ", ft_strjoin_ml(ms, message, " « "));
	mess = ft_strjoin_ml(ms, mess, ft_strjoin_ml(ms, elem, " »\n"));
	return (mess);
}

bool	ft_err(t_mshell *mshell, char *message, char *elem, int exit_code)
{
	ft_putstr_fd(ft_build_err_mess(mshell, message, elem), 2);
	g_exit_code = exit_code;
	ft_free_ml(mshell);
	return (false);
}

void	ft_mem_err(t_mshell *mshell)
{
	g_exit_code = 1; // ou ENOMEM == 12
	perror("malloc: ");
	ft_exit_cleanly(mshell);
}
