/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/05/09 18:21:27 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_token	*ft_lexer(t_mshell *mshell, t_mnode **ml)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer);
	if (ft_validate_operators(&lexer, mshell->input) == false)
		return (NULL); // erreur a gerer
	ft_input_one_space(&lexer, mshell->input, ml);
	ft_build_list_token(&lexer, ml);
	mshell->list_token = lexer.list_token;
	ft_print_list_token(mshell->list_token); //ASUPP
	return (lexer.list_token);
}
