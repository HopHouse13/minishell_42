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
	if ((qts->dbl_q && str[i] != '\"' && str[i] != '\\' && str[i] != '$')
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
		if (qts->spl_q)
			qts->spl_q = OUT;
		if (qts->dbl_q)
			qts->dbl_q = OUT;
		qts->delay_out = false;
	}
}

// printf pour la verif
// printf("\tsimple  %d\tdouble  %d\tin_q  %d\t\t[ %c ]\n", qts->spl_q,
// 	qts->dbl_q, qts->in_q, str[i]);
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
	return (qts->in_q);
}
