/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:47 by pab               #+#    #+#             */
/*   Updated: 2025/05/21 17:21:32 by pbret            ###   ########.fr       */
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
	
	/* if (line[exp->start] == '\0')
		return (ft_strdup_ml(mshell, "$")); */ // voir si c'est utilse ou pas
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
	//ev_ptr = ft_get_env(ev_name, mshell->env_list);
	ev_ptr = getenv(ev_name); // ASUPP
	if (ev_ptr)
		ev_expanded = ft_strdup_ml(mshell, ev_ptr);
	else
		ev_expanded = NULL; // renvoie le signal qu'il faut stopper le processus d'expand et continuer a analyser les char suivants
	return (ev_expanded);
}

char	*ft_expand_hd(t_mshell *mshell, char *line, t_hd *hd)
{
	int	i;
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
				i =  i + (ft_strlen(ev_exp) -1);
			}
		}
	}
	return (line);
}

void	ft_put_in_hd(t_mshell *mshell, char *line, t_cmd *cmd)
{
	if (ft_escape_last_char(line)) // si  '\' est a la fin de line, fait l'enlever + pas de retour de ligne
	{
		line = ft_substr_ml(mshell, line, 0, ft_strlen(line) -1);
		write(cmd->fd_hd, line, ft_strlen(line));
	}
	else
	{
		write(cmd->fd_hd, line, ft_strlen(line));
		write(cmd->fd_hd, "\n", 1);
	}
	//printf("\n>>>>> result [%s]\n\n\n", line); // ASUPP
}
// if (line == NULL)
// {
// 	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2);
// 	ft_putstr_fd(cmd->delim_hd, 2);
// 	ft_putstr_fd("')\n", 2);
// 	break ;
// }
void	ft_heredoc(t_mshell *mshell, t_cmd *cmd)
{
	t_hd		hd;
	char		*value_rdl;
	char		*line;
	
	while (1)
	{
		value_rdl = readline("> ");
		if (value_rdl == NULL)
			break; // voir le commantaire au dessus
		if (!ft_strcmp(value_rdl, cmd->delim_hd))
			break ;
		line = ft_strdup_ml(mshell, value_rdl);
		free(value_rdl);
		if (cmd->expand_hd && ft_found_dollar_active(line))
			line = ft_expand_hd(mshell, line, &hd);
		ft_put_in_hd(mshell, line, cmd);	
		ft_free_one_node_ml(line, &mshell->ml);
	}
	close(cmd->fd_hd);
	cmd->fd_hd = -1;
}

// 2 problemes:

// quand $VAR valide mais n'hexiste pas, ca fait ligne vide alors qu'il faudrait affichier tout brut ($hello -> $hello)
// quand $VAR invalide, ca fait buguer voir ligne 32 dans ko_exp_hd

// NOTE HEREDOC

// Qu'un niveau d'expand:
// si une $VAR expanded dans le heredoc, a une autre $VAR dedans, la 2eme ne doit pas etre expanded mais affichee brute.
// WARNING par contre elle doit l'etre endehors d'un heredoc.

// Une seule regles pour les KO:
// si $VAR invalid ou valid mais n'hexiste pas -> print brut

// Zero regles pour les quotes:
// toutes les quotes sont print bruts
