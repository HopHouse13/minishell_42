/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:17:37 by pbret             #+#    #+#             */
/*   Updated: 2025/04/02 21:23:35 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Met à jour l'état d'un type de guillemet (simple ou double).
// Si le guillemet est ouvert, il est fermé et le marqueur est mis à OUT_Q.
// S'il est fermé, il est ouvert et le marqueur est mis à OUT_Q seulement si
// aucun autre guillemet n'était déjà actif.
void	ft_status_upd(bool *quote, bool *mark, bool *flag)
{
	if (*quote == IN_Q)
	{
		*quote = OUT_Q;
		*mark = OUT_Q;
	}	
	else 
	{
		*quote = IN_Q;
		if (*flag == OUT_Q)
		{
			*mark = OUT_Q;
			*flag = IN_Q;
		}
	}
}

// Gère l'état des guillemets dans le lexer en fonction du caractère analysé.
// Vérifie l'ouverture et la fermeture des guillemets simples et doubles,
// en prenant en compte les caractères d'échappement.
// Retourne l'état du marqueur `mark_q` après traitement du caractère.
bool	ft_inside_quotes_lexer(t_lexer *lexer, char *str, int i)
{
	if (lexer->flag_q == IN_Q)
	{
		lexer->flag_q = OUT_Q;
		lexer->mark_q = IN_Q;
	}
	if (!ft_effect_escape(lexer, str, i))
	{
		if (str[i] == '\'' && lexer->double_q == OUT_Q)
			ft_status_upd(&lexer->simple_q, &lexer->mark_q, &lexer->flag_q);
		else if (str[i] == '\"' && lexer->simple_q == OUT_Q)
			ft_status_upd(&lexer->double_q, &lexer->mark_q, &lexer->flag_q);
	}
	printf("\tsimple_q: %d\tdouble_q: %d\tmark_q: %d\tchar: [%c]\n", lexer->simple_q, lexer->double_q, lexer->mark_q, str[i]);
	return (lexer->mark_q);
}