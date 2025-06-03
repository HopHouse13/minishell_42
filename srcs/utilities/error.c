/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:50 by pbret             #+#    #+#             */
/*   Updated: 2025/06/03 20:53:35 by pbret            ###   ########.fr       */
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
	g_exit_code = exit_code;  // faut il un code erreur pour syntax?????
	ft_free_ml(ms);
	return (false);
}

void	ft_mem_err(t_mshell *mshell)
{
	g_exit_code = 1; // errno ou ENOMEM == 12
	perror("malloc: impossible d'allouer la mémoire");
	ft_exit_cleanly(mshell);
}

bool	ft_fd_err(t_mshell *mshell, char *file)
{
	g_exit_code = errno; // ???
	perror(file);
	ft_free_ml(mshell);
	return (false);
}

void	ft_hd_err(int *fd, char *delim)
{
	close(*fd);
	*fd = -1;
	unlink("/tmp/heredoc_tmp.txt");
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted \" ", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd(" \")\n", 2);
}

void	ft_main_err(t_mshell *mshell)
{
	g_exit_code = 1; // ???
	ft_putstr_fd("exit\n", 2);
	ft_exit_cleanly(mshell);
}
