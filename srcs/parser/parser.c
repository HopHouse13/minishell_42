/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:36 by pbret             #+#    #+#             */
/*   Updated: 2025/03/01 18:48:04 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_build_list_tokens(t_mshell *mshell, t_parser *lexer, char *input)
// {
// 	while(input[++(parser->i)])
// 	{
// 		if (ft_is_space(input[parser->i]) && parser->intoken)
// 		{
// 			parser->intoken = false;
// /* 			if (input[parser->i + 1] && !ft_is_space(input[parser->i + 1]))
// 				ft_add_node(mshell, input[parser->i]); */
// 		}
// 		else if (ft_is_notredirection(input[parser->i]))
// 			//blabla
// 		else if (ft_is_chevron(input[parser->i]))
// 			if (input[parser->i] == input[parser->i + 1])
// 				// un seul element (<< ou >>)
// 			else
// 				// (< ou >)
// 		else if (ft_is_pipe(input[parser->i]))
// 			// changement de node
// 	}
// }

// void	ft_parser(t_mshell *mshell, char *input)
// {
// 	t_parser	lexer;

// 	ft_init_parser(&lexer); // a completer au fur et a mesure
// 	ft_build_list_tokens(mshell, input, &lexer); // a faire
// }