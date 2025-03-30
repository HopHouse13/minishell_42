/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:12:08 by pbret             #+#    #+#             */
/*   Updated: 2025/03/10 12:38:48 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// ft pour gerer l'initialisation de  la liste
void	ft_list_manag(char *cmds_brut)
{
	
}

// ft pour creer le 1er noeud de la liste avec le pointeur head qui pointe dessus
void	ft_init_head_list_token(t_list **list)
{
	t_list	*first_node;
	
	first_node = malloc(sizeof(t_list));
	if (!first_node)
	{
		perror("initialization list ");
		ft_master_free(list);
		return ;
	}
	first_node->cmds = NULL;
	first_node->prev = NULL;
	first_node->next = NULL;
	*list = first_node;
}
// ft pour ajOUT_Qer un noeud a la fin de la liste.
void	ft_add_node_end(t_list **list)
{
	t_list	*tmp;
	t_list	*new_node;
	
	if (!*list)
	{
		ft_init_head_list_token(list);
		return ;
	}
	new_node = malloc(sizeof (t_list));
	if (!new_node)
	{
		perror("initialization list ");
		return ;
	}
	tmp = *list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new_node->cmds = NULL;
	new_node->prev = tmp;
	new_node->next = NULL;
	tmp->next = new_node;
}
// ft pour ajOUT_Qer un noeud au milieu de la liste.