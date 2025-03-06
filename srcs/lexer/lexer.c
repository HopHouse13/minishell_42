/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/03/06 15:33:33 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_token	*ft_lexer(char *input)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer);
	if (ft_validate_operators(&lexer, input) == false)
		return (NULL); // erreur a gerer
	ft_input_one_space(&lexer, input);
	ft_build_list_token(&lexer);
	// ft_print_list_token(lexer.list_token);
	// ft_free_list_token(&lexer);
	return (lexer.list_token);
}
