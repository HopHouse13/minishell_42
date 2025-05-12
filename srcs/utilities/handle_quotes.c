/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:28:07 by pab               #+#    #+#             */
/*   Updated: 2025/05/11 14:29:28 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_apply_delay(bool *quote, bool *delay)
{
	*quote = OUT;
	*delay = false;
}

// Met à jour l'état d'un type de guillemet (simple ou double).
// Si le guillemet est ouvert, il est fermé et le marqueur est mis à OUT.
// S'il est fermé, il est ouvert et le marqueur est mis à OUT seulement si
// aucun autre guillemet n'était déjà actif.
void	ft_stt_up(bool *quote, bool *mark, bool *flag, bool *delay)
{
	if (*quote == IN)
		*delay = true;	
	else 
	{
		*quote = IN;
		if (*flag == OUT)
		{
			*mark = OUT;
			*flag = IN;
		}
	}
}

// Gère l'état des guillemets dans le qts en fonction du caractère analysé.
// Vérifie l'ouverture et la fermeture des guillemets simples et doubles,
// en prenant en compte les caractères d'échappement.
// Retourne l'état du marqueur `mark_q` après traitement du caractère.
//  si 1 -> IN ; si 0 -> OUT;
bool	ft_status_qts(t_qts *qts, char *str, int i)
{
	if (i == 0)
	{
		qts->simple_q = OUT;
		qts->double_q = OUT;
		qts->flag_q = OUT;
		qts->mark_q = OUT;
		qts->delay_sq = false;
		qts->delay_dq = false;
	}
	if (qts->delay_sq)
		ft_apply_delay(&qts->simple_q, &qts->delay_sq);
	if (qts->delay_dq)
		ft_apply_delay(&qts->double_q, &qts->delay_dq);
	if (qts->flag_q == IN)
	{
		qts->flag_q = OUT;
		qts->mark_q = IN;
	}
	if (str[i] == '\'' && qts->double_q == OUT && !ft_effect_esc(qts, str, i))
		ft_stt_up(&qts->simple_q, &qts->mark_q, &qts->flag_q, &qts->delay_sq);
	if (str[i] == '\"' && qts->simple_q == OUT && !ft_effect_esc(qts, str, i))
		ft_stt_up(&qts->double_q, &qts->mark_q, &qts->flag_q, &qts->delay_dq);
	printf("\tsimple_q: %d\tdouble_q: %d\tmark_q: %d\tchar [%c]\n", qts->simple_q, qts->double_q, qts->mark_q, str[i]);
	return (qts->mark_q);
}

// Si le nombre de changement d'etat de on_off est:
// impair	-> 	pas d'effet
// pair		->	effet
// [\] pas d'effet dans simple quote
// dans double quotes pas d'effet sauf avec ["][\][$]
// false (0) -> pas d'effet ; true (1) -> effet
bool	ft_effect_esc(t_qts *qts, char *str, int i)
{
	bool	on_off;
	
	on_off = false;
	if((qts->double_q && str[i] != '\"' && str[i] != '\\' && str[i] != '$')
		|| qts->simple_q)
		return (on_off);
	while (--i >= 0 && str[i] == '\\')
		on_off = !on_off;
	return (on_off);
}
