/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/05/12 21:46:38 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parser(t_parser *parser, t_token *list_token)
{
	parser->i = -1;
	parser->list_token = list_token;
	parser->list_cmd = NULL;
	parser->start = -1;
	parser->end = -1;
	parser->mark_b = OUT;
}


