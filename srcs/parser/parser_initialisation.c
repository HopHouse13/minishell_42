/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/04/02 12:48:24 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parser(t_mshell *mshell, t_parser *parser, t_token *list_token)
{
	parser->i = -1;
	parser->list_token = list_token;
	parser->list_cmd = NULL;
	parser->env = mshell->env;
	parser->simple_q = OUT_Q;
	parser->double_q = OUT_Q;
	parser->mark_q = OUT_Q;
	parser->start = -1;
	parser->end = -1;
	parser->exit_status = -1;
}


