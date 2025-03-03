/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/03/03 19:51:43 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer(t_mshell *mshell, char *input)
{
	t_lexer	lexer;

	ft_init_lexer(&lexer);
	if (ft_validate_operators(&lexer, input) == false)
		return ; // a gerer
	ft_cleaning_input(&lexer, input);
	ft_build_list_tokens(&lexer);
	(void)mshell->input;
}

// grep "mot"<input.txt|wc -l&&echo "bien:$HOME"'Pas bien:$HOME'>output.txt
// grep "mot" < input.txt | wc -l