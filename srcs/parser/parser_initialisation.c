/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:15 by pbret             #+#    #+#             */
/*   Updated: 2025/03/10 13:04:38 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parser(t_parser *parser, t_token *list_token)
{
	parser->i = -1;
	parser->list_token = list_token;
	parser->list_cmd = NULL;
}


