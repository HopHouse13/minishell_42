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

bool	ft_effect_esc(t_qts *qts, char *str, int i)
{
	bool	on_off;
	
	on_off = false;
	if((qts->dbl_q && str[i] != '\"' && str[i] != '\\' && str[i] != '$')
		|| qts->spl_q)
		return (on_off);
	while (--i >= 0 && str[i] == '\\')
		on_off = !on_off;
	return (on_off);
}

// Reset l'état des quotes
void	init_qts(t_qts *qts)
{
	qts->spl_q = OUT;
	qts->dbl_q = OUT;
	qts->in_q = OUT;
	qts->delay_in = false;
	qts->delay_out = false;
}

void	ft_swipe(bool *quote, bool *status, bool *delay_in, bool *delay_out)
{
	if (*quote == OUT)
	{
		*quote = IN;
		*delay_in = true;
	}
	else
	{	
		*status = OUT;
		*delay_out = true;
	}
}
void	ft_delay(t_qts *qts)
{
	if (qts->delay_in)
	{
		qts->in_q = IN;
		qts->delay_in = false;
	}
	if (qts->delay_out)
	{
		if(qts->spl_q)
			qts->spl_q = OUT;
		if(qts->dbl_q)
			qts->dbl_q = OUT;
		qts->delay_out = false;
	}
}

bool	ft_status_qts(t_qts *qts, char *str, int i)
{
	if (i == 0)
		init_qts(qts);
	if (qts->delay_in || qts->delay_out)
		ft_delay(qts);
	if (str[i] == '\'' && qts->dbl_q == OUT && !ft_effect_esc(qts, str, i))
		ft_swipe(&qts->spl_q, &qts->in_q, &qts->delay_in, &qts->delay_out);
	else if (str[i] == '\"' && qts->spl_q == OUT && !ft_effect_esc(qts, str, i))
		ft_swipe(&qts->dbl_q, &qts->in_q, &qts->delay_in, &qts->delay_out);
	// printf("\tsimple  %d\tdouble  %d\tin_q  %d\t\t[ %c ]\n", qts->spl_q, qts->dbl_q, qts->in_q, str[i]);
	return (qts->in_q);
}


// void	ft_apply_delay(bool *quote, bool *delay)
// {
// 	*quote = OUT;
// 	*delay = false;
// }

// // Met à jour l'état d'un type de guillemet (simple ou double).
// // Si le guillemet est ouvert, il est fermé et le marqueur est mis à OUT.
// // S'il est fermé, il est ouvert et le marqueur est mis à OUT seulement si
// // aucun autre guillemet n'était déjà actif.
// void	ft_stt_up(bool *quote, bool *mark, bool *flag, bool *delay)
// {
// 	if (*quote == IN)
// 		*delay = true;	
// 	else 
// 	{
// 		*quote = IN;
// 		if (*flag == OUT)
// 		{
// 			*mark = OUT;
// 			*flag = IN;
// 		}
// 	}
// }

// // Gère l'état des guillemets dans le qts en fonction du caractère analysé.
// // Vérifie l'ouverture et la fermeture des guillemets simples et doubles,
// // en prenant en compte les caractères d'échappement.
// // Retourne l'état du marqueur `in_q` après traitement du caractère.
// //  si 1 -> IN ; si 0 -> OUT;
// bool	ft_status_qts(t_qts *qts, char *str, int i)
// {
// 	if (i == 0)
// 	{
// 		qts->spl_q = OUT;
// 		qts->dbl_q = OUT;
// 		qts->flag_q = OUT;
// 		qts->in_q = OUT;
// 		qts->delay_sq = false;
// 		qts->delay_dq = false;
// 	}
// 	if (qts->delay_sq)
// 		ft_apply_delay(&qts->spl_q, &qts->delay_sq);
// 	if (qts->delay_dq)
// 		ft_apply_delay(&qts->dbl_q, &qts->delay_dq);
// 	if (qts->flag_q == IN)
// 	{
// 		qts->flag_q = OUT;
// 		qts->in_q = IN;
// 	}
// 	if (str[i] == '\'' && qts->dbl_q == OUT && !ft_effect_esc(qts, str, i))
// 		ft_stt_up(&qts->spl_q, &qts->in_q, &qts->flag_q, &qts->delay_sq);
// 	if (str[i] == '\"' && qts->spl_q == OUT && !ft_effect_esc(qts, str, i))
// 		ft_stt_up(&qts->dbl_q, &qts->in_q, &qts->flag_q, &qts->delay_dq);
// 	printf("\tsimple_q: %d\tdouble_q: %d\tin_q: %d\tchar [%c]\n", qts->spl_q, qts->dbl_q, qts->in_q, str[i]);
// 	return (qts->in_q);
// }

// Si le nombre de changement d'etat de on_off est:
// impair	-> 	pas d'effet
// pair		->	effet
// [\] pas d'effet dans simple quote
// dans double quotes pas d'effet sauf avec ["][\][$]
// false (0) -> pas d'effet ; true (1) -> effet
