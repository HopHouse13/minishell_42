/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_list_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:39:56 by pbret             #+#    #+#             */
/*   Updated: 2025/04/18 19:05:16 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_define_token_elem(t_lexer *lexer)
{
	t_token *tmp;

	tmp = lexer->list_token;
	while (tmp->token != END)
	{
		if (tmp->token == PIPE)
			lexer->cmd_in_pipe = false;
		if (tmp->token == ELEM)
		{
			if (tmp->prev && tmp->prev->token == R_IN) // <
				tmp->token = F_IN;
			else if (tmp->prev && tmp->prev->token == R_OUT) // >
				tmp->token = F_OUT;
			else if (tmp->prev && tmp->prev->token == APPEND) // >>
				tmp->token = F_APP;
			else if (tmp->prev && tmp->prev->token == HD) // <<
				tmp->token = DELIM;
			else if (tmp->token == ELEM && !lexer->cmd_in_pipe)
				tmp->token = ft_builtin_or_cmd(lexer, tmp->elem);
			else
				tmp->token = ARG;
		}
		tmp = tmp->next;
	}
}

void ft_define_token_redir(t_lexer *lexer)
{
	t_token *tmp;

	tmp = lexer->list_token;
	while (tmp)
	{
		if (!ft_strcmp(tmp->elem, "|"))
			tmp->token = PIPE;
		else if (!ft_strcmp(tmp->elem, "<"))
			tmp->token = R_IN;
		else if (!ft_strcmp(tmp->elem, ">"))
			tmp->token = R_OUT;
		else if (!ft_strcmp(tmp->elem, "<<"))
			tmp->token = HD;
		else if (!ft_strcmp(tmp->elem, ">>"))
			tmp->token = APPEND;
		else if (!ft_strcmp(tmp->elem, ">"))
			tmp->token = R_OUT;
		else if (!ft_strcmp(tmp->elem, ">"))
			tmp->token = R_OUT;
		else if (!ft_strcmp(tmp->elem, ";"))
			tmp->token = END;
		else
			tmp->token = ELEM;
		tmp = tmp->next;
	}
}

void ft_init_head_list_token(t_token **list_token, char *elem, t_mnode **ml)
{
	t_token *first_node;

	first_node = ft_malloc_list(sizeof(t_token), ml);
	if (!first_node)
	{
		perror("initialization list ");
		// ft_master_free(list_token);
		return;
	}
	first_node->elem = elem;
	first_node->token = -1;
	first_node->prev = NULL;
	first_node->next = NULL;
	*list_token = first_node;
}

void ft_add_node(t_lexer *lexer, char *elem, t_mnode **ml)
{
	t_token *tmp;
	t_token *new_elem;

	if (!lexer->list_token)
	{
		ft_init_head_list_token(&(lexer->list_token), elem, ml);
		return;
	}
	new_elem = ft_malloc_list(sizeof(t_token), ml);
	if (!new_elem)
	{
		perror("initialization list ");
		// ft_master_free(list);
		return;
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

void ft_build_list_token(t_lexer *lexer, t_mnode **ml)
{
	int start;

	lexer->i = 0;
	lexer->j = 0; // len de la sous chaine
	start = 0;	  // debut de la sous chaine
	while (lexer->input_clear[lexer->i])
	{
		start = lexer->i;
		while (lexer->input_clear[lexer->i] && lexer->input_clear[lexer->i] != ' ')
		{
			lexer->j++;		
			lexer->i++;
		}
		//printf("\tline: [%s]\tstart: [%d]\tlen : [%d]\n", lexer->input_clear, start, lexer->j);
		ft_add_node(lexer, ft_substr_ml(lexer->input_clear, start, lexer->j, ml), ml);
		lexer->j = 0;
		if (lexer->input_clear[lexer->i] == ' ')
			lexer->i++;
	}
	ft_define_token_redir(lexer);
	ft_define_token_elem(lexer);
	// ft_clear_empty_node(parser, ml); // A FAIRE uniquement pour le '\' isole
}
