/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:57:59 by pbret             #+#    #+#             */
/*   Updated: 2025/06/18 18:14:30 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_parser(t_mshell *mshell)
{/* printf("\n\t|||||||||||||||||||||| PARSER |||||||||||||||||||||||\n\n"); // ASUPP */
	t_parser	parser;

	ft_init_parser(&parser, mshell->list_token);
	ft_clear_and_expand(mshell, &parser);
	if (!ft_valid_syntax(mshell, &parser))
		return (false);
	if (!ft_init_list_cmd(mshell, &parser))
		return (false);
	if (!ft_fill_list_cmd(mshell, &parser))
		return (false);
	mshell->count_pipe = ft_count_pipe(&parser);
	ft_print_list_cmd(mshell); // ASUPP
	return (true);
}
