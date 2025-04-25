/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:47 by pab               #+#    #+#             */
/*   Updated: 2025/04/25 18:28:39 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_merge_hd(char *line, char *ev_exp, t_hd *exp, t_mnode **ml)
{
	char	*before;
	char	*after;
	char	*str_merge;
	
	before = ft_substr_ml(line, 0, exp->start -1, ml);
	after = ft_substr_ml(line, exp->end, ft_strlen(line), ml);
	str_merge = ft_strjoin_ml(before, ft_strjoin_ml(ev_exp, after, ml), ml);
	return (str_merge);
}

char	*ft_expand_hd(char *line, t_hd *exp, t_mnode **ml)
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
		return (NULL);
	exp->end = exp->start;
	while (ft_isalnum(line[exp->end]) || line[exp->end] == '_')
		exp->end++;
	ev_name = ft_substr_ml(line, exp->start, exp->end - exp->start, ml);
	ev_ptr = getenv(ev_name);
	if (ev_ptr)
		ev_expanded = ft_strdup_ml(ev_ptr, ml);
	else
		ev_expanded = NULL; // renvoie le signal qu'il faut stopper le processus d'expand et continuer a analyser les char suivants
	return (ev_expanded);
}

char	*ft_expand_elem_hd(char *line, t_hd *exp, t_mnode **ml)
{
	int	i;
	char	*ev_exp;
	
	exp->start = 0;
	exp->end = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			exp->start = i +1;
			ev_exp = ft_expand_hd(line, exp, ml);
			if (ev_exp)
			{	
				line = ft_merge_hd(line, ev_exp, exp, ml);
				i =  i + (ft_strlen(ev_exp) -1);
			}
		}
	}
	return (line); // <<<<<<<<<<<<<<<<<<<<<<<<<< ici ft_strdup
}
// if (line == NULL)
// {
// 	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2);
// 	ft_putstr_fd(cmd->delim_hd, 2);
// 	ft_putstr_fd("')\n", 2);
// 	break ;
// }
void	ft_heredoc(t_cmd *cmd, t_mnode **ml)
{
	t_hd		exp;
	char		*line;
	char		*tmp;
	
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break; // voir le commantaire au dessus
		if (!ft_strcmp(line, cmd->delim_hd))
			break ;
		if (cmd->expand_hd && ft_found_dollar_active(line))
		{
			tmp = line; // pas obliger de faire un tmp, en renvoyant tjs une char* different du depart
			line = ft_expand_elem_hd(line, &exp, ml);
			free(tmp);
			tmp = NULL;
		}
		printf("\n\n>>>>> line final [%s]\n\n\n", line); // ASUPP
		write(cmd->fd_hd, line, ft_strlen(line));
		if (ft_return_to_line(line))
			write(cmd->fd_hd, "\n", 1);
		ft_free_one_node_ml(line, ml);
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