/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:57:59 by pbret             #+#    #+#             */
/*   Updated: 2025/06/12 17:42:28 by pab              ###   ########.fr       */
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
	ft_init_list_cmd(mshell, &parser);
	if (!ft_fill_list_cmd(mshell, &parser))
		return (false);
	mshell->count_pipe = ft_count_pipe(&parser);
	// ft_print_list_cmd(mshell); // ASUPP
	return (true);
}
