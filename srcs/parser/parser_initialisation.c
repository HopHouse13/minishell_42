/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/05/09 12:51:56 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parser(t_parser *parser, t_token *list_token)
{
	parser->i = -1;
	parser->list_token = list_token;
	parser->list_cmd = NULL;
	parser->simple_q = OUT;
	parser->double_q = OUT;
	parser->flag_q = OUT;
	parser->mark_q = OUT;
	parser->start = -1;
	parser->end = -1;
	parser->mark_b = OUT;
}


