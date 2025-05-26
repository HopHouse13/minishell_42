/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear_and_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/05/26 22:05:49 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear_and_expand(t_mshell *mshell, t_parser *parser)
{
	ft_printf("\n\tvvvvvvvvvvvvvvvvvvv EXPAND_CLEAR vvvvvvvvvvvvvvvvvvvv\n");
	ft_printf("\n\t------------------ expand_markers -------------------\n\n");
	ft_mark_expand(mshell, parser);
	ft_print_list_token(parser->list_token);
	ft_printf("\n\t---------- clear_escape_char_and_quotes -------------\n\n");
	ft_clear_elems(mshell, parser);
	ft_print_list_token(parser->list_token);
	ft_printf("\n\t--------------------- expand ------------------------\n\n");
	ft_expand_list(mshell, parser);
	ft_print_list_token(parser->list_token);
}
