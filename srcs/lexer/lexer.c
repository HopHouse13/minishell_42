/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/02/19 18:26:36 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// bash-5.1$    < in    grep z  |wc -l>OUT_Q   $
//" "' ' d""

// void	ft_build_list_tokens(t_mshell *mshell, t_lexer *lexer, char *input)
// {
// 	while(input[++(lexer->i)])
// 	{
// 		if (ft_is_space(input[lexer->i]) && lexer->intoken)
// 		{
// 			lexer->intoken = false;
// /* 			if (input[lexer->i + 1] && !ft_is_space(input[lexer->i + 1]))
// 				ft_add_node(mshell, input[lexer->i]); */
// 		}
// 		else if (ft_is_notredirection(input[lexer->i]))
// 			//blabla
// 		else if (ft_is_chevron(input[lexer->i]))
// 			if (input[lexer->i] == input[lexer->i + 1])
// 				// un seul element (<< ou >>)
// 			else
// 				// (< ou >)
// 		else if (ft_is_pipe(input[lexer->i]))
// 			// changement de node
// 	}
// }

// void	ft_lexer(t_mshell *mshell, char *input)
// {
// 	t_lexer	lexer;

// 	ft_init_lexer(&lexer); // a completer au fur et a mesure
// 	ft_build_list_tokens(mshell, input, &lexer); // a faire
// }