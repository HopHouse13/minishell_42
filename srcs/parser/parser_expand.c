/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:16:51 by pab               #+#    #+#             */
/*   Updated: 2025/04/13 17:48:51 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_merge(char *str, char *ev_exp, t_parser *parser, t_mnode **ml)
{
	char	*before;
	char	*after;
	char	*str_merged;
	
	before = ft_substr_ml(str, 0, parser->start - 2, ml); // -2 car on veut une len et pas un indexe donc +1 pour passer d'un indexe a une len ET comme [start] = 'H' $[HOME]; [start-3] = carac devant $ DONC -3 + 1 = -2
	after = ft_substr_ml(str, parser->end + 1, ft_strlen(str), ml);
	str_merged = ft_strjoin_ml(before, ft_strjoin_ml(ev_exp, after, ml), ml);
	return (str_merged);
}

char	*ft_expand(char *elem, int i, t_parser *parser, t_mnode **ml)
{
	char	*ev_name;
	char	*ev_ptr;
	char	*ev_expanded;
	
//	if (ft_invalid_name(elem, i))
	parser->start = i + 2; // pour arriver a la 1er carac du nom. ex : $[HOME] i = $ ; i+2 = H
	//printf("\nVALUE CARAC debut : %c\n\n", elem[parser->start]);
	if (elem[parser->start] == '?')
	{
		parser->end = parser->start + 1;
		// return (ft_itoa_ml(exit_status)); // dernier exit status
	}
	if (!ft_isalpha(elem[parser->start]) && elem[parser->start] != '_')
	{
		parser->end = parser->start + 1;
		return ("");
	}
	parser->end = parser->start;
	while (elem[parser->end] && elem[parser->end] != ']')
		parser->end++;
	// printf("\nVALUE CARAC FIN : %c\n\n", elem[parser->end]);
	ev_name = ft_substr_ml(elem, parser->start, parser->end - parser->start, ml); // end(carac : ']') - start = l'indexe du dernier carac et commme nous voulons une len -> +1 ; c'est pour ca que decrmente end apres cette ligne.
	// parser->end--; // pour avoir uniquement le nom de la VAR
	printf("\n\tEV_NAME : %s\n\n", ev_name);
	ev_ptr = getenv(ev_name); // voir comment gerer les variables d'env car je pense qu'il y a double actuellement
	if (ev_ptr)
		ev_expanded = ft_strdup_ml(ev_ptr, ml);
	else
		ev_expanded = ft_strdup_ml("", ml);
	return (ev_expanded);
}

void	ft_expand_elem(t_token *tmp, t_parser *parser, t_mnode **ml)
{
	int		i;
	char	*ev_exp;
	
	i = -1;
	while (tmp->elem[++i])
	{
		ft_inside_quotes_parser(parser, tmp->elem, i);
		if (tmp->elem[i] == '$'
			&& parser->simple_q == OUT
			&& tmp->token != DELIM
			&& tmp->elem[i + 1]
			&& tmp->elem[i + 1] == '['
			&& (i == 0 || !ft_effect_escape_parser(parser, tmp->elem, i-1)))
		{
			ev_exp = ft_expand(tmp->elem, i, parser, ml);
			if (!ev_exp)
			{
				dprintf(2, "\nINVALID_NAME_EXPAND");
				return ;
			}
			printf("\n\tExppanded : %s\n\n", ev_exp);
			tmp->elem = ft_merge(tmp->elem, ev_exp, parser, ml);
			i = -1;
		}
	}
}

void	ft_expand_list(t_parser *parser, t_mnode **ml)
{
	t_token *tmp;
	
	tmp = parser->list_token;
	while (tmp && tmp->token != END)
	{
		ft_expand_elem(tmp, parser, ml);
		printf("\n\n\tELEM_FINAL : %s\n\n", tmp->elem); // ASUPP
		tmp = tmp->next;
	}
}

// un probleme:
// -> gestion du 1er caractere invalide -> bash interprete le $ et le caractere invalide literalement.
// ex : $@HOME -> $@HOME	|	$\HOME -> $HOME (car le carac d'escape est supprimer a la fin)


// bash-5.1$ echo $ \HOME
// $HOME
// bash-5.1$ echo $ "HOME"
// HOME
// bash-5.1$ echo $ .HOME
// $.HOME


// autre probleme:
// input -> $$ pas gerer