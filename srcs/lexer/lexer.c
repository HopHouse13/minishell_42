/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/05/12 22:35:30 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	ft_lexer(t_mshell *mshell, t_mnode **ml)
{
	t_lexer	lexer;

	printf("\n\t||||||||||||||||||||||  LEXER  ||||||||||||||||||||||\n"); // ASUPP
	ft_init_lexer(&lexer);
	if (!ft_validate_operators(mshell, &lexer, mshell->input))
		return (1); // erreur a gerer
	ft_input_one_space(mshell, &lexer, ml);
	ft_build_list_token(mshell, &lexer, ml);
	ft_print_list_token(mshell->list_token); //ASUPP
	return (0);
}
