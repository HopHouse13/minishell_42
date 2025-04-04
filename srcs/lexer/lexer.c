/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/04/04 16:32:09 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_token	*ft_lexer(char *input, t_mnode **ml)
{(void)ml;
	t_lexer	lexer;
	ml = NULL;
	ft_init_lexer(&lexer);
	if (ft_validate_operators(&lexer, input) == false)
		return (NULL); // erreur a gerer
	ft_input_one_space(&lexer, input);
	ft_build_list_token(&lexer, ml);
	return (lexer.list_token);
}
