/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:47 by pab               #+#    #+#             */
/*   Updated: 2025/06/13 14:28:43 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_merge_hd(t_mshell *mshell, char *line, char *ev_exp, t_hd *hd)
{
	char	*before;
	char	*after;
	char	*merge;

	before = ft_substr_ml(mshell, line, 0, hd->start -1);
	after = ft_substr_ml(mshell, line, hd->end, ft_strlen(line));
	merge = ft_strjoin_ml(mshell, before, ft_strjoin_ml(mshell, ev_exp, after));
	return (merge);
}

char	*ft_expand_ev_hd(t_mshell *mshell, char *line, t_hd *hd)
{
	char	*ev_name;
	char	*ev_ptr;
	char	*ev_expanded;

	if (line[hd->start] == '?')
	{
		hd->end = hd->start +1;
		return (ft_itoa_ml(mshell, g_exit_code));
	}
	if (!ft_isalpha(line[hd->start]) && line[hd->start] != '_')
		return (NULL);
	hd->end = hd->start;
	while (ft_isalnum(line[hd->end]) || line[hd->end] == '_')
		hd->end++;
	ev_name = ft_substr_ml(mshell, line, hd->start, hd->end - hd->start);
	ev_ptr = ft_found_value_key(mshell, ev_name);
	if (ev_ptr)
		ev_expanded = ft_strdup_ml(mshell, ev_ptr);
	else
		ev_expanded = NULL;
	return (ev_expanded);
}

char	*ft_expand_hd(t_mshell *mshell, char *line, t_hd *hd)
{
	int		i;
	char	*ev_exp;

	hd->start = 0;
	hd->end = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			hd->start = i +1;
			ev_exp = ft_expand_ev_hd(mshell, line, hd);
			if (ev_exp)
			{
				line = ft_merge_hd(mshell, line, ev_exp, hd);
				i = i + (ft_strlen(ev_exp) - 1);
			}
		}
	}
	return (line);
}

// (1er if) si '\' est a la fin de line, fait l'enlever + pas de retour de ligne
void	ft_put_in_hd(t_mshell *mshell, char *line, t_cmd *cmd)
{
	if (ft_escape_last_char(line))
	{
		line = ft_substr_ml(mshell, line, 0, ft_strlen(line) - 1);
		write(cmd->fd_in, line, ft_strlen(line));
	}
	else
	{
		write(cmd->fd_in, line, ft_strlen(line));
		write(cmd->fd_in, "\n", 1);
	}
}

void	ft_heredoc(t_mshell *mshell, t_cmd *cmd)
{
	t_hd		hd;
	char		*value_rdl;
	char		*line;

	while (1)
	{
		value_rdl = readline("> ");
		if (value_rdl == NULL)
		{
			ft_hd_err(&cmd->fd_in, cmd->delim_hd);
			break ;
		}
		if (!ft_strcmp(value_rdl, cmd->delim_hd))
			break ;
		line = ft_strdup_ml(mshell, value_rdl);
		free(value_rdl);
		if (cmd->expand_hd && ft_found_dollar_active(line))
			line = ft_expand_hd(mshell, line, &hd);
		ft_put_in_hd(mshell, line, cmd);
		ft_free_one_node_ml(line, &mshell->ml);
	}
	// close(cmd->fd_hd); // le fermer dans l'execution
	// cmd->fd_hd = -1; // et le mettre a -1 apres l'avoir close
}
