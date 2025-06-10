/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:59:48 by pab               #+#    #+#             */
/*   Updated: 2025/06/10 10:17:49 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_path_access(char *cmd)
{
	if (access(cmd, F_OK) == -1) // + X_OK pour verif droit d'execution
		exit(127); // commande not found
	if (access(cmd, X_OK) == -1)
		exit(126); // pas executable
	return (1);
}