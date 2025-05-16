/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/05/16 19:15:03 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	ft_lexer(t_mshell *mshell, t_mnode **ml)
{
	t_lexer	lexer;

	printf("\n\t||||||||||||||||||||||  LEXER  ||||||||||||||||||||||\n"); // ASUPP
	ft_init_lexer(mshell, &lexer, ml);
	if (!ft_character_valid(mshell, mshell->input, ml))
		return (1);
	ft_cleaning_input(mshell, &lexer, ml);
	ft_build_list_token(mshell, &lexer, ml);
	ft_print_list_token(mshell->list_token); //ASUPP
	return (0);
}
	