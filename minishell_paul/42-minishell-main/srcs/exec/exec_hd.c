/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_write(t_token *tp, int fd_in, t_data **data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_exit_status == 130)
		{
			if (!line)
				ft_heredoc_error(tp->next->value);
			break ;
		}
		if (tp->next->was_quote == false)
			line = handle_dollar(line, data);
		if (!ft_strcmp(line, tp->next->value))
			break ;
		write(fd_in, line, ft_strlen(line));
		write(fd_in, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
}

int	init_here_doc(t_token *tp, t_data **data)
{
	int	infile;

	infile = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0)
		return (-1);
	ft_signals(3);
	g_exit_status = 0;
	here_doc_write(tp, infile, data);
	ft_signals(2);
	if (g_exit_status == 130)
	{
		close(infile);
		unlink("temp.txt");
		return (-1);
	}
	close(infile);
	infile = open("temp.txt", O_RDONLY);
	return (infile);
}
