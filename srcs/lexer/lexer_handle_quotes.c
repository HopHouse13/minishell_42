// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   lexer_handle_quotes.c                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/02 21:17:37 by pbret             #+#    #+#             */
// /*   Updated: 2025/04/09 18:08:58 by pbret            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// // Met à jour l'état d'un type de guillemet (simple ou double).
// // Si le guillemet est ouvert, il est fermé et le marqueur est mis à OUT.
// // S'il est fermé, il est ouvert et le marqueur est mis à OUT seulement si
// // aucun autre guillemet n'était déjà actif.
// void	ft_status_update_lexer(bool *quote, bool *mark, bool *flag)
// {
// 	if (*quote == IN)
// 	{
// 		*quote = OUT;
// 		*mark = OUT;
// 	}	
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

// // Gère l'état des guillemets dans le lexer en fonction du caractère analysé.
// // Vérifie l'ouverture et la fermeture des guillemets simples et doubles,
// // en prenant en compte les caractères d'échappement.
// // Retourne l'état du marqueur `mark_q` après traitement du caractère.
// //  si 1 -> IN ; si 0 -> OUT;
// bool	ft_inside_quotes_lexer(t_lexer *lexer, char *str, int i)
// {
// 	if (i == 0)
// 	{
// 		lexer->simple_q = OUT;
// 		lexer->double_q = OUT;
// 		lexer->flag_q = OUT;
// 		lexer->mark_q = OUT;
// 	}
// 	if (lexer->flag_q == IN)
// 	{
// 		lexer->flag_q = OUT;
// 		lexer->mark_q = IN;
// 	}
// 	if (!ft_effect_escape_lexer(lexer, str, i))
// 	{
// 		if (str[i] == '\'' && lexer->double_q == OUT)
// 			ft_status_update_lexer(&lexer->simple_q,
// 			&lexer->mark_q, &lexer->flag_q);
// 		else if (str[i] == '\"' && lexer->simple_q == OUT)
// 			ft_status_update_lexer(&lexer->double_q,
// 			&lexer->mark_q, &lexer->flag_q);
// 	}
// 	printf("\tsimple_q: %d\tdouble_q: %d\tmark_q: %d\tchar [%c]\n", lexer->simple_q, lexer->double_q, lexer->mark_q, str[i]);
// 	return (lexer->mark_q);
// }
