/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/04/13 18:12:25 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parser(t_mshell *mshell, t_parser *parser, t_token *list_token)
{
	(void)mshell;
	parser->i = -1;
	parser->list_token = list_token;
	parser->list_cmd = NULL;
	//parser->env = mshell->env;
	parser->simple_q = OUT;
	parser->double_q = OUT;
	parser->flag_q = OUT;
	parser->mark_q = OUT;
	parser->start = -1;
	parser->end = -1;
	parser->mark_b = OUT;
	parser->exit_status = -1;
}


