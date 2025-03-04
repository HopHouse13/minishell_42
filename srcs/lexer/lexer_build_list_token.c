/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_list_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:39:56 by pbret             #+#    #+#             */
/*   Updated: 2025/03/04 17:51:51 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_define_token(t_lexer *lexer)
{
	t_token	*tmp;
	
	tmp = lexer->list_tokens;
	while (tmp)
	{
		if (!ft_strncmp(lexer->list_tokens->elem, "|", ft_strlen("|")))
			lexer->list_tokens->token = PIPE;
		else if (!ft_strncmp(lexer->list_tokens->elem, "<", ft_strlen("<")))
			lexer->list_tokens->token = REDIR_IN;
		else if (!ft_strncmp(lexer->list_tokens->elem, ">", ft_strlen(">")))
			lexer->list_tokens->token = REDIR_OUT;
		else if (!ft_strncmp(lexer->list_tokens->elem, "<<", ft_strlen("<<")))
			lexer->list_tokens->token = HD;
		else if (!ft_strncmp(lexer->list_tokens->elem, ">>", ft_strlen(">>")))
			lexer->list_tokens->token = APPEND;
		else if (!ft_strncmp(lexer->list_tokens->elem, ">", ft_strlen(">")))
			lexer->list_tokens->token = REDIR_OUT;
		else if (!ft_strncmp(lexer->list_tokens->elem, ">", ft_strlen(">")))
			lexer->list_tokens->token = REDIR_OUT;
		else
			lexer->list_tokens->token = WORD;
		tmp = tmp->next;
	}
}

void	ft_init_list_head(t_token **list_tokens, char *elem)
{
	t_token	*fist_node;
	
	fist_node = malloc(sizeof(t_token));
	if (!fist_node)
	{
		perror("initialization list ");
		//ft_master_free(list_tokens);
		return ;
	}
	fist_node->elem = elem;
	fist_node->token = -1;
	fist_node->prev = NULL;
	fist_node->next = NULL;
	*list_tokens = fist_node;
}

void	ft_add_node_token(t_lexer *lexer, char *elem)
{
	t_token	*tmp_head;
	t_token	*new_elem;
	
	if (!lexer->list_tokens)
	{
		ft_init_list_head(&(lexer->list_tokens), elem);
		return ;
	}
	new_elem = malloc(sizeof (t_token));
	if (!new_elem)
	{
		perror("initialization list ");
		//ft_master_free(list);
		return ;
	}
	tmp_head = lexer->list_tokens;
	while (tmp_head->next != NULL)
		tmp_head = tmp_head->next;
	new_elem->elem = elem;
	new_elem->token = -1;
	new_elem->prev = tmp_head;
	new_elem->next = NULL;
	tmp_head->next = new_elem;
}

void	ft_build_list_tokens(t_lexer *lexer)
{
	int	start;

	lexer->i = -1;
	lexer->j = 0; //len de la sous chaine
	start = 0; // debut de la sous chaine
	while (lexer->line[++lexer->i])
	{
		start = lexer->i;
		while (lexer->line[lexer->i] != ' ' && lexer->line[lexer->i++])
			lexer->j++;
		ft_add_node_token(lexer, ft_substr(lexer->line, start, lexer->j));
		lexer->j = 0;
	}
}
