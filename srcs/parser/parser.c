/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_parser(t_mshell *mshell)
{printf("\n\t|||||||||||||||||||||| PARSER |||||||||||||||||||||||\n\n");
	t_parser	parser;

	ft_init_parser(&parser, mshell->list_token);
	ft_clear_and_expand(mshell, &parser);
	if (!ft_valid_syntax(mshell, &parser))
		return (false);
	ft_init_list_cmd(mshell, &parser);
	if (!ft_fill_list_cmd(mshell, &parser))
		return (false);
	mshell->count_pipe = ft_count_pipe(&parser);
	ft_print_list_cmd(mshell); // ASUPP
	return (true);

}

// ATTENTION -> lors de la comparaison des commandes qui prennent une redir_in (comme cat), le '\' est mal gere. (< in "ca\t") ET  < in ca\"t ( la quote est enlevee) PAS BON
// exterieur:		si actif -> agit puis disparait
//					si inactif -> disparait
//
// dans double_q: 	si actif -> agit puis disparait
//					is inactif -> est affichie comme un carac std

// echo c\at
// cat

// echo c\\at
// c\at

// echo "c\at"
// c\at

// echo "c\\at" $ \ "
// c\at
