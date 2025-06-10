/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear_and_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/06/10 10:31:50 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear_and_expand(t_mshell *mshell, t_parser *parser)
{
	// ft_printf("\n\tvvvvvvvvvvvvvvvvvvv EXPAND_CLEAR vvvvvvvvvvvvvvvvvvvv\n"); // ASUPP
	// ft_printf("\n\t------------------ expand_markers -------------------\n\n"); // ASUPP
	ft_mark_expand(mshell, parser);
	// ft_print_list_token(parser->list_token); // ASUPP
	// ft_printf("\n\t---------- clear_escape_char_and_quotes -------------\n\n"); // ASUPP
	ft_clear_elems(mshell, parser);
	// ft_print_list_token(parser->list_token); // ASUPP
	// ft_printf("\n\t--------------------- expand ------------------------\n\n"); // ASUPP
	ft_expand_list(mshell, parser);
	// ft_print_list_token(parser->list_token); // ASUPP
}
