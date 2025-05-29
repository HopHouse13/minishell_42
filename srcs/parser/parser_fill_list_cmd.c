/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser)
{
	if (!ft_handle_redir(mshell, parser))
		return (false);
	ft_handle_cmd(mshell, parser);
	if (!ft_handle_hd(mshell, parser))
		return (false);
	mshell->list_cmd = parser->list_cmd;
	return (true);
}
