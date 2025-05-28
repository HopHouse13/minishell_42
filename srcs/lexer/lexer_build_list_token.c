/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_list_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:39:56 by pbret             #+#    #+#             */
/*   Updated: 2025/05/29 00:00:11 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_define_token_elem(t_lexer *lexer)
{
	t_token	*tmp;

	tmp = lexer->list_token;
	while (tmp->token != END)
	{
		if (tmp->token == PIPE)
			lexer->cmd_in_pipe = false;
		if (tmp->token == ELEM)
		{
			if (tmp->prev && tmp->prev->token == R_IN)
				tmp->token = F_IN;
			else if (tmp->prev && tmp->prev->token == R_OUT)
				tmp->token = F_OUT;
			else if (tmp->prev && tmp->prev->token == APPEND)
				tmp->token = F_APP;
			else if (tmp->prev && tmp->prev->token == HD)
				tmp->token = DELIM;
			else if (tmp->token == ELEM && !lexer->cmd_in_pipe)
				tmp->token = ft_builtin_or_cmd(lexer, tmp->elem);
			else
				tmp->token = ARG;
		}
		tmp = tmp->next;
	}
}

void	ft_define_token_redir(t_lexer *lexer)
{
	t_token	*tmp;

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

void	ft_init_head_list_token(t_mshell *mshell, t_token **list_t, char *elem)
{
	t_token	*first_node;

	first_node = ft_malloc_list(mshell, sizeof(t_token));
	first_node->elem = elem;
	first_node->token = -1;
	first_node->prev = NULL;
	first_node->next = NULL;
	*list_t = first_node;
}

void	ft_add(t_mshell *mshell, t_lexer *lexer, char *elem)
{
	t_token	*tmp;
	t_token	*new_elem;

	if (!lexer->list_token)
	{
		ft_init_head_list_token(mshell, &(lexer->list_token), elem);
		return ;
	}
	new_elem = ft_malloc_list(mshell, sizeof(t_token));
	tmp = lexer->list_token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new_elem->elem = elem;
	new_elem->token = -1;
	new_elem->prev = tmp;
	new_elem->next = NULL;
	tmp->next = new_elem;
}

void	ft_build_list_token(t_mshell *mshell, t_lexer *lexer)
{printf(">>>> [%s]\n\n", lexer->clear_input);
	int	i;
	int	j;
	int	srt;

	i = 0;
	j = 0;
	srt = 0;
	while (lexer->clear_input[i])
	{
		srt = i;
		while (lexer->clear_input[i] && !ft_isspace(lexer->clear_input[i]))
		{printf("test\n");
			j++;
			i++;
		}
		ft_add(mshell, lexer, ft_substr_ml(mshell, lexer->clear_input, srt, j));
		j = 0;
		while (ft_isspace(lexer->clear_input[i]))
			i++;
	}
	ft_define_token_redir(lexer);						
	ft_define_token_elem(lexer);
	mshell->list_token = lexer->list_token;
	ft_print_list_token(mshell->list_token);
}

