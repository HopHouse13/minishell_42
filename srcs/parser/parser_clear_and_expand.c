/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear_and_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:34:58 by pab               #+#    #+#             */
/*   Updated: 2025/06/20 11:35:10 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear_and_expand(t_mshell *mshell, t_parser *parser)
{
	ft_mark_expand(mshell, parser);
	ft_clear_elems(mshell, parser);
	ft_expand_list(mshell, parser);
}
