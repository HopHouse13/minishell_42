/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser)
{
	ft_handle_redir(parser);
	ft_handle_cmd(mshell, parser);
	ft_handle_hd(mshell, parser);
	mshell->list_cmd = parser->list_cmd;

}
