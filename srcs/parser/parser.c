/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:57:59 by pbret             #+#    #+#             */
/*   Updated: 2025/06/20 11:12:50 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_parser(t_mshell *mshell)
{
	t_parser	parser;

	ft_init_parser(&parser, mshell->list_token);
	ft_clear_and_expand(mshell, &parser);
	if (!ft_valid_syntax(mshell, &parser))
		return (false);
	ft_init_list_cmd(mshell, &parser);
	if (!ft_fill_list_cmd(mshell, &parser))
		return (false);
	mshell->count_pipe = ft_count_pipe(&parser);
	return (true);
}
