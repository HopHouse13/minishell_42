/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:47 by pab               #+#    #+#             */
/*   Updated: 2025/04/25 02:13:11 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_ko_exp_hd(char *line, char *ev_exp, t_exp_hd *exp, t_mnode **ml)
{
	char	*before;
	char	*after;
	char	*middle;
	char	*str_merge;
	
	str_merge = NULL;
	before = ft_substr_ml(line, 0, exp->start -1, ml);
	after = ft_substr_ml(line, exp->end + 1, ft_strlen(line), ml);
	if (ev_exp[0] == '\"' || ev_exp[0] == '\'')
		str_merge = ft_strjoin_ml(before, ft_strjoin_ml("", after, ml), ml);
	else if (ev_exp[0] == '\\')
		str_merge = ft_strjoin_ml(before, ft_strjoin_ml("$", after, ml), ml);
	else
	{
		middle = ft_strjoin_ml("$", ev_exp, ml);
		str_merge = ft_strjoin_ml(before, ft_strjoin_ml(middle, after, ml), ml); // probleme
	}
	return (str_merge);
}

char	*ft_merge_hd(char *line, char *ev_exp, t_exp_hd *exp, t_mnode **ml)
{
	char	*before;
	char	*after;
	char	*str_merge;
	
	if (!ft_isalpha(line[exp->start]) && line[exp->start] != '_')
		str_merge = ft_ko_exp_hd(line, ev_exp, exp, ml);
	else
	{	
		before = ft_substr_ml(line, 0, exp->start -1, ml);
		after = ft_substr_ml(line, exp->end, ft_strlen(line), ml);
		str_merge = ft_strjoin_ml(before, ft_strjoin_ml(ev_exp, after, ml), ml);
	}
	return (str_merge);
}

char	*ft_expand_hd(char *line, t_exp_hd *exp, t_mnode **ml)
{	
	char	*ev_name;
	char	*ev_ptr;
	char	*ev_expanded;
	
	/* if (line[exp->start] == '\0')
		return (ft_strdup_ml("$", ml)); */ // voir si c'est utilse ou pas
	if (line[exp->start] == '?')
	{
		exp->end = exp->start + 1;
		// return (ft_itoa_ml(exit_status)); // dernier exit status
	}
	if (!ft_isalpha(line[exp->start]) && line[exp->start] != '_')
		return (ft_substr_ml(line, exp->start, 1, ml));
	exp->end = exp->start;
	while (ft_isalnum(line[exp->end]) || line[exp->end] == '_')
		exp->end++;
	ev_name = ft_substr_ml(line, exp->start, exp->end - exp->start, ml);
	ev_ptr = getenv(ev_name);
	if (ev_ptr)
		ev_expanded = ft_strdup_ml(ev_ptr, ml);
	else
		ev_expanded = ft_strdup_ml("", ml);
	return (ev_expanded);
}

char	*ft_expand_elem_hd(char *line, t_exp_hd *exp, t_mnode **ml)
{
	int	i;
	char	*ev_exp;
	
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			exp->start = i +1;
			ev_exp = ft_expand_hd(line, exp, ml);
			line = ft_merge_hd(line, ev_exp, exp, ml);
			i = -1;
		}
	}
	return (line);
}
// si $VAR le no est valid mais elle ne'existe pas -> faut affichier le dollar et son nom texto (pas rien comme endehors du heredoc)
void	ft_heredoc(t_cmd *cmd, t_mnode **ml)
{
	t_exp_hd	exp;
	char		*line;
	char		*tmp;
	
	/* exp.start = 0;
	exp.end = 0; */       // voir si c'est utlise ou pas
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (!ft_strcmp(line, cmd->delim_hd))
			break ;
		if (cmd->expand_hd && ft_found_dollar_active(line))
		{
			tmp = line;
			line = ft_expand_elem_hd(line, &exp, ml);
			free(tmp);
		}
		write(cmd->fd_hd, line, ft_strlen(line));
		write(cmd->fd_hd, "\n", 1);
		ft_free_one_node_ml(line, ml);
	}
	close(cmd->fd_hd);
	cmd->fd_hd = -1;
}

// 2 problemes:

// quand $VAR valide mais n'hexiste pas, ca fait ligne vide alors qu'il faudrait affichier tout brut ($hello -> $hello)
// quand $VAR invalide, ca fait buguer voir ligne 32 dans ko_exp_hd