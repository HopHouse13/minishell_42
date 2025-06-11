/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:09:03 by pbret             #+#    #+#             */
/*   Updated: 2025/06/11 16:44:36 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser)
{
	if (!ft_handle_redir(mshell, parser))
		return (false);
	ft_handle_cmd(mshell, parser);
	// if (!ft_handle_hd(mshell, parser))
		// return (false);
	mshell->list_cmd = parser->list_cmd;
	return (true);
}
