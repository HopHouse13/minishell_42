/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/03/04 17:55:06 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_list_tokens(t_lexer *lexer)
{
	t_token	*tmp;

	if (!lexer->list_tokens)
		return ;
	while (lexer->list_tokens)
	{
		tmp = lexer->list_tokens;
		lexer->list_tokens = lexer->list_tokens->next;
		free(tmp->elem);
		free(tmp);
	}
	lexer->list_tokens = NULL;
}

void	ft_lexer(t_mshell *mshell, char *input)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer);
	if (ft_validate_operators(&lexer, input) == false)
		return ; // a gerer
	ft_input_one_space(&lexer, input);
	ft_build_list_tokens(&lexer);
	ft_printf("test\n");	
	ft_define_token(&lexer);
	ft_print_list_tokens(lexer.list_tokens);
	ft_free_list_tokens(&lexer);
	(void)mshell->input;
}
	