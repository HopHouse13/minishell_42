/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:25:47 by phautena          #+#    #+#             */
/*   Updated: 2025/06/18 13:36:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_code = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_child_slash(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

static void	handle_child_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

static void	handle_heredoc(int sig)
{
	(void)sig;
	g_exit_code = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	// ioctl(STDIN_FILENO, TIOCSTI, "");
}

void	ft_signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, &handle_child_c);
		signal(SIGQUIT, &handle_child_slash);
	}
	else if (mode == 3)
	{
		signal(SIGINT, &handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
