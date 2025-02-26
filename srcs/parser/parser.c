/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:55 by pbret             #+#    #+#             */
/*   Updated: 2025/02/26 01:05:33 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_parcer(t_parser *parser)
{
	ft_init_line(parser->line);
	parser->i = -1;
	parser->j = -1;
	parser->squote = OUT_Q;
	parser->dquote = OUT_Q;
	parser->flag_quote = OUT_Q;
}
// "|, ||, &&"
bool	ft_control_operators_valid(t_parser *parser, char *input)
{
	int	a;

	parser->i = -1;
	while (input[++parser->i])
	{
		ft_check_quotes(parser, input[parser->i]);
		if (input[parser->i] == '&' && parser->flag_quote == OUT_Q)
			return (false);
		else if (input[parser->i] == '|' && parser->flag_quote == OUT_Q)
		{
			a = parser->i + 1;
			while (input[a])
			{
				ft_check_quotes(parser, input[parser->i]);
				if (input[a] == '|')
					return (false);
				if (input[a] != ' ')
					break ;
				a++;
			}
			parser->i = a - 1;
		}
	}
	return (true);
}

bool	ft_quotes_valid(t_parser *parser, char *input)
{
	while (input[++parser->i])
		ft_check_quotes(parser, input[parser->i]);
	if (parser->flag_quote == OUT_Q)
		return (true);
	return (false);
}

void	ft_check_quotes(t_parser *parser, char c)
{
	if (c == '\'' && parser->dquote == OUT_Q && parser->squote == OUT_Q)
		parser->squote = IN_Q;
	else if (c == '\'' && parser->squote == IN_Q && parser->dquote == OUT_Q)
		parser->squote = OUT_Q;
	else if (c == '\"' && parser->squote == OUT_Q && parser->dquote == OUT_Q)
		parser->dquote = IN_Q;
	else if (c == '\"' && parser->dquote == IN_Q && parser->squote == OUT_Q)
		parser->dquote = OUT_Q;
	if (parser->squote == OUT_Q && parser->dquote == OUT_Q)
		parser->flag_quote = OUT_Q;
	else
		parser->flag_quote = IN_Q; 
}

void	ft_put_pipe(t_parser *parser, char *input)
{
	if (input[parser->i - 1] != ' ')
		ft_handle_space(parser, input);
	parser->line[++parser->j] = '|';
	if (input[parser->i + 1] != ' ')
		ft_handle_space(parser, input);
}

void	ft_put_redirection(t_parser *parser, char *input)
{
	if (input[parser->i - 1] != ' ')
		parser->line[++parser->j] = ' ';
	if (input[parser->i] == '<')
	{
		parser->line[++parser->j] = '<';
		if (input[parser->i + 1] == '<')
		{
			parser->line[++parser->j] = '<';
			parser->i++;
		}
	}
	else if (input[parser->i] == '>')
	{
		parser->line[++parser->j] = '>';
		if (input[parser->i + 1] == '>')
		{
			parser->line[++parser->j] = '>';
			parser->i++;
		}
	}
	if (input[parser->i + 1] != ' ')
		parser->line[++parser->j] = ' ';

}

void	ft_put_spaces(t_parser *parser, char *input)
{

	parser->i = 0;
	while (input[parser->i])
	{
		ft_check_quotes(parser, input[parser->i]);
		if (input[parser->i] == '|' && parser->flag_quote == OUT_Q)
			ft_put_pipe(parser, input);
		else if ((input[parser->i] == '<' || input[parser->i] == '>') && parser->flag_quote == OUT_Q)
			ft_put_redirection(parser, input);
		else if (input[parser->i] == ' ' && parser->flag_quote == OUT_Q)
			ft_handle_space(parser, input);
		else
			parser->line[++parser->j] = input[parser->i];
		parser->i++;
	}
	ft_printf("\nline : [%s]\n\n", parser->line);
}
bool	ft_input_valid(t_parser *parser, char *input) // !!!!!!!!!!!!!! gerer les redirection non conforme : "<< <" "> >" "<<>>"
{
	if (ft_quotes_valid(parser, input) == false)
		return (printf("false_quote\n"), false); // erreur a gerer
	if (ft_control_operators_valid(parser, input) == false)
		return (printf("false_operators\n"), false); // erreur a gerer
	return (true);	
}	

void	ft_parser(t_mshell *mshell, char *input)
{
	t_parser	parser;

	ft_init_parcer(&parser);
	if (ft_input_valid(&parser, input) == false)
		return ; // a gerer
	printf("value check_input [%d]\n", ft_input_valid(&parser, input));
	ft_put_spaces(&parser, input);
	(void)mshell->input;
}

// grep "mot"<input.txt|wc -l&&echo "bien:$HOME"'Pas bien:$HOME'>output.txt
// grep "mot" < input.txt | wc -l && echo "bien : $HOME" 'Pas bien : $HOME' > output.txt