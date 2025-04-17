/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/04/17 18:48:32 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_token	*ft_lexer(char *input, t_mnode **ml)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer);
	if (ft_validate_operators(&lexer, input) == false)
		return (NULL); // erreur a gerer
	ft_input_one_space(&lexer, input, ml);
	int i=-1;
	while(lexer.input_clear[++i] != '\0')
		printf("\ncarac input :%c\n", lexer.input_clear[i]);
	ft_build_list_token(&lexer, ml);
	return (lexer.list_token);
}
