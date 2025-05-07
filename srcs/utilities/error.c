/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:50 by pbret             #+#    #+#             */
/*   Updated: 2025/05/07 15:59:17 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
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

void	ft_sys_error(int )
{
	
}