/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:50 by pbret             #+#    #+#             */
/*   Updated: 2025/05/10 17:38:26 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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