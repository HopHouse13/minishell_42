/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:50 by pbret             #+#    #+#             */
/*   Updated: 2025/05/21 14:51:38 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_build_err_mess(t_mshell *ms, char *message, char *elem)
{
	char	*mess;

	mess = NULL;
	mess = ft_strjoin_ml(ms, "minishell: ", ft_strjoin_ml(ms, message, " « "));
	mess = ft_strjoin_ml(ms, mess, ft_strjoin_ml(ms, elem," »\n"));
	return (mess);
}

bool	ft_err(t_mshell *mshell, char *message, char *elem, int exit_code)
{
	ft_putstr_fd(ft_build_err_mess(mshell, message, elem), 2);
	g_exit_code = exit_code;
	ft_free_ml(mshell);
	return (false);
}

// void	ft_fatal_error(char *message, int exit_code)
// {
// 	g_exit_code = exit_code;
// 	perror(message);
// 	// ft_clear_mshell();
// 	exit(g_exit_code);
// }
// gestion d'erreur:

// Avant d'exit et d'afficher un message d'erreur, il faut free l'ensemble des malloc dont le malloc du main (t_mshell)
// si errno est non null -> afficher son message
// sinon ecrire dans errno puis l'afficher

// exemple gpt
// int handle_sys_error(t_minishell *sh, const char *context_msg, int exit_flag)
// {
//     perror(context_msg);          // perror affiche le message système (errno)
//     cleanup_all(sh);              // ta fonction personnalisée pour libérer la mémoire
//     if (exit_flag)
//         exit(EXIT_FAILURE);       // exit seulement si erreur fatale
//     return (1);                   // sinon retour d’un code d’erreur
// }

// void	ft_sys_error(int )
// {

// }

// EXIT_CODE:
// 2 : builtin, malloc