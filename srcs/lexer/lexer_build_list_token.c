/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_list_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:39:56 by pbret             #+#    #+#             */
/*   Updated: 2025/03/19 18:24:37 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_define_token(t_lexer *lexer)
{
	t_token	*tmp;

	tmp = lexer->list_token;
	while (tmp)
	{
		if (!ft_strcmp(tmp->elem, "|"))
			tmp->token = PIPE;
		else if (!ft_strcmp(tmp->elem, "<"))
			tmp->token = REDIR_IN;
		else if (!ft_strcmp(tmp->elem, ">"))
			tmp->token = REDIR_OUT;
		else if (!ft_strcmp(tmp->elem, "<<"))
			tmp->token = HD;
		else if (!ft_strcmp(tmp->elem, ">>"))
			tmp->token = APPEND;
		else if (!ft_strcmp(tmp->elem, ">"))
			tmp->token = REDIR_OUT;
		else if (!ft_strcmp(tmp->elem, ">"))
			tmp->token = REDIR_OUT;
		else if (!ft_strcmp(tmp->elem, ";"))
			tmp->token = END;
		else
			tmp->token = ELEM;
		tmp = tmp->next;
	}
}

void	ft_init_head_list_token(t_token **list_token, char *elem, t_mnode **ml)
{
	t_token	*first_node;
	
	first_node = ft_malloc_list(sizeof(t_token), ml);
	if (!first_node)
	{
		perror("initialization list ");
		//ft_master_free(list_token);
		return ;
	}
	first_node->elem = elem;
	first_node->token = -1;
	first_node->prev = NULL;
	first_node->next = NULL;
	*list_token = first_node;
}

void	ft_add_node_token(t_lexer *lexer, char *elem, t_mnode **ml)
{
	t_token	*tmp;
	t_token	*new_elem;
	
	if (!lexer->list_token)
	{
		ft_init_head_list_token(&(lexer->list_token), elem, ml);
		return ;
	}
	new_elem = ft_malloc_list(sizeof (t_token), ml);
	if (!new_elem)
	{
		perror("initialization list ");
		//ft_master_free(list);
		return ;
	}
	tmp = lexer->list_token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new_elem->elem = elem;
	new_elem->token = -1;
	new_elem->prev = tmp;
	new_elem->next = NULL;
	tmp->next = new_elem;
}

void	ft_build_list_token(t_lexer *lexer, t_mnode **ml)
{
	int	start;

	lexer->i = -1;
	lexer->j = 0; // len de la sous chaine
	start = 0; // debut de la sous chaine
	while (lexer->line[++lexer->i])
	{
		start = lexer->i;
		while (lexer->line[lexer->i] != ' ' && lexer->line[lexer->i++])
			lexer->j++;
		ft_add_node_token(lexer, ft_substr_ml(lexer->line, start, lexer->j, ml), ml);
		lexer->j = 0;
	}
	ft_define_token(lexer);
}
