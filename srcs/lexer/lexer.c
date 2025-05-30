/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/05/26 21:40:37 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lexer(t_mshell *mshell)
{
	t_lexer	lexer;

	printf("\n\t||||||||||||||||||||||  LEXER  ||||||||||||||||||||||\n");
	ft_init_lexer(mshell, &lexer);
	if (!ft_character_valid(mshell, mshell->input))
		return (1);
	ft_cleaning_input(mshell, &lexer);
	ft_build_list_token(mshell, &lexer);
	ft_print_list_token(mshell->list_token);
	return (0);
}
