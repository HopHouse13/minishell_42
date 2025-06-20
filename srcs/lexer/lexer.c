/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/06/20 11:41:45 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_lexer(t_mshell *mshell)
{
	t_lexer	lexer;

	ft_init_lexer(mshell, &lexer);
	if (!ft_character_valid(mshell, mshell->input))
		return (false);
	ft_cleaning_input(mshell, &lexer);
	ft_build_list_token(mshell, &lexer);
	return (true);
}
