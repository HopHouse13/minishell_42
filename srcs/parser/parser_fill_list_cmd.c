/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_list_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fill_list_cmd(t_mshell *mshell, t_parser *parser, t_mnode **ml)
{
	ft_handle_redir(parser);
	ft_handle_cmd(parser, ml);
	ft_handle_hd(mshell, parser, ml);
	mshell->list_cmd = parser->list_cmd;

}
