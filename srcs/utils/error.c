/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:50 by pbret             #+#    #+#             */
/*   Updated: 2025/02/18 15:57:52 by pbret            ###   ########.fr       */
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