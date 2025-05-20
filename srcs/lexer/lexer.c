/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/05/20 11:00:51 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	ft_lexer(t_mshell *mshell)
{
	t_lexer	lexer;

	printf("\n\t||||||||||||||||||||||  LEXER  ||||||||||||||||||||||\n"); // ASUPP
	ft_init_lexer(mshell, &lexer);
	if (!ft_character_valid(mshell, mshell->input))
		return (1);
	ft_cleaning_input(mshell, &lexer);
	ft_build_list_token(mshell, &lexer);
	ft_print_list_token(mshell->list_token); //ASUPP
	return (0);
}
	