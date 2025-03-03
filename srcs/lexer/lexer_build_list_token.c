/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_list_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:39:56 by pbret             #+#    #+#             */
/*   Updated: 2025/03/03 20:13:35 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_list_tokens(t_token *head)
{
    t_token *tmp = head;
    while ( tmp->next != NULL)
    {
        printf("Token: %s, Type: %d\n", tmp->elem, tmp->token);
        tmp = tmp->next;
    }
}

void	ft_init_list_head(t_token **list, char *elem)
{
	t_token	*fist_node;
	
	fist_node = malloc(sizeof(t_token));
	if (!fist_node)
	{
		perror("initialization list ");
		//ft_master_free(list);
		return ;
	}
	fist_node->elem = elem;
	fist_node->token = 0;
	fist_node->prev = NULL;
	fist_node->next = NULL;
	*list = fist_node;
}

void	ft_add_node_token(t_lexer *lexer, char *elem)
{
	t_token	*new_elem;
	t_token	*tmp_head;
	
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
		while (lexer->line[lexer->i] && lexer->line[lexer->i] == ' ')
			lexer->i++;
		if (lexer->line[lexer->i] != ' ' && start == 0)
			start = lexer->i;
		while (lexer->line[lexer->i] && lexer->line[lexer->i] != ' ' )
			lexer->j++;
		if (start != 0)
		{	
			ft_add_node_token(lexer, ft_substr(lexer->line, start, lexer->j));
			start = 0;
			lexer->j = 0;
		}
	}
	ft_print_list_tokens(lexer->list_tokens);
}

	/* while (lexer->(list_tokens->next))
	{
		ft_printf("\n%s\t%d\n", lexer->list_tokens->elem, lexer->list_tokens->token);
		lexer->list_tokens = lexer->list_tokens->next;
	}

 */