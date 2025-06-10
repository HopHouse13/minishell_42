/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/06/10 10:34:54 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_lexer(t_mshell *mshell)
{/* printf("\n\t||||||||||||||||||||||  LEXER  ||||||||||||||||||||||\n"); // ASUPP */
	t_lexer	lexer;

	ft_init_lexer(mshell, &lexer);
	if (!ft_character_valid(mshell, mshell->input))
		return (false);
	ft_cleaning_input(mshell, &lexer);
	ft_build_list_token(mshell, &lexer);
	// ft_print_list_token(mshell->list_token); // ASUPP
	return (true);
}
