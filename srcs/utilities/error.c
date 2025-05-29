/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:50 by pbret             #+#    #+#             */
/*   Updated: 2025/05/29 19:24:23 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_syntax_err(t_mshell *ms, char *elem, int exit_code)
{
	char	*mess;

	mess = NULL;
	mess = ft_strjoin_ml(ms, "minishell: ", ft_strjoin_ml
			(ms, "erreur de syntaxe près du symbole inattendu", " « "));
	mess = ft_strjoin_ml(ms, mess, ft_strjoin_ml(ms, elem, " »\n"));
	ft_putstr_fd(mess, 2);
	g_exit_code = exit_code;
	ft_free_ml(ms);
	return (false); // faut il un code erreur pour syntax?????
}

void	ft_mem_err(t_mshell *mshell)
{
	g_exit_code = 1; // errno ou ENOMEM == 12
	perror("malloc: impossible d'allouer la mémoire");
	ft_exit_cleanly(mshell);
}

bool	ft_open_err(t_mshell *mshell, char *file)
{
	g_exit_code = errno; // ???
	perror(file);
	ft_free_ml(mshell);
	return (false);
}
