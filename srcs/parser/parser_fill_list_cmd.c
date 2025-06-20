/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:09:03 by pbret             #+#    #+#             */
/*   Updated: 2025/06/20 11:39:06 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser)
{
	init_redirections(mshell, parser);
	ft_handle_cmd(mshell, parser);
	mshell->list_cmd = parser->list_cmd;
	return (true);
}
